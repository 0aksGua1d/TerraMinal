#include <regex>
#include "StatesLoader1.h"
#include "utils/string_converter.h"

#include "logger/Logger.h"

#include "con_script/ConLocation.h"
#include "con_script/ops/int/ConOpAdd.h"
#include "con_script/ops/scope/ConExitScope.h"
#include "con_script/ops/scope/ConEnterScope.h"
#include "con_script/ops/scope/ConEnterWeakScope.h"
#include "con_script/ops/control/ConMove.h"
#include "con_script/ops/int_map/ConIntMapGet.h"
#include "con_script/ops/control/ConCondition.h"
#include "con_script/ops/control/ConCall.h"
#include "con_script/ops/vector/ConVectorGet.h"

#include "renderable/Frame.h"
#include "renderable/Animation.h"
#include "renderable/RenderableState.h"

const std::wregex START_STATE_REGEX(L"^start_state:(\\w+)$", std::wregex::optimize);
const std::wregex NAME_REGEX(L"^name:(\\w+)$", std::wregex::optimize);
const std::wregex ANIMATION_REGEX(L"^anim:(\\d+)$", std::wregex::optimize);
const std::wregex HANDLERS_COUNT_REGEX(L"^handlers:(\\d+)$", std::wregex::optimize);
const std::wregex HANDLER_REGEX(L"^(\\w+):(\\w+)(?:-(\\d+))?(?:-(\\w\\d+))?(?:-(\\w))?$", std::wregex::optimize);
const std::wregex FRAME_CALLBACKS_COUNT_REGEX(L"^frame_callbacks:(\\d+)$", std::wregex::optimize);
const std::wregex FRAME_CALLBACK_REGEX(L"^(\\d+)-(\\w+)$", std::wregex::optimize);

using ConRegs = ConScript::ConRegs;
using ConOp = ConScript::ConOp;
using ConLocation = ConScript::ConLocation;
using ConFunction = ConScript::ConFunction;

using ConOpMove = ConScript::ConOpMove;
using ConOpCondition = ConScript::ConOpCondition;
using ConOpCall = ConScript::ConOpCall;
using ConOpEnterWeakScope = ConScript::ConOpEnterWeakScope;
using ConOpEnterScope = ConScript::ConOpEnterScope;
using ConOpExitScope = ConScript::ConOpExitScope;
using ConOpAdd = ConScript::ConOpAdd;
using ConOpIntMapGet = ConScript::ConOpIntMapGet;
using ConOpVectorGet = ConScript::ConOpVectorGet;


bool StatesLoader1::can_parse(const ParsedState& current_parsing_state) {
    return nullptr != current_parsing_state.anims;
}

static std::shared_ptr<std::map<std::wstring, std::shared_ptr<ConFunction>>> default_state_scope_functions = nullptr;

static std::shared_ptr<Scope> get_default_state_scope() {
    if (nullptr == default_state_scope_functions) {
        default_state_scope_functions = std::make_shared<std::map<std::wstring, std::shared_ptr<ConFunction>>>();
        std::vector<std::shared_ptr<RenderableState>> states;
        std::vector<std::any> init_data{};
        auto ops = std::make_shared<std::vector<std::shared_ptr<ConOp>>>();

        ops->push_back(std::make_shared<ConOpIntMapGet>(
                ConLocation(ConLocation::SECTION::STACK, (std::wstring)L"frame_callbacks"),
                ConLocation(ConLocation::SECTION::ARGUMENTS, 0),
                ConLocation(ConLocation::SECTION::REGS, ConRegs::LOCATION::REG_1)));

        auto condition_ops = std::make_shared<std::vector<std::shared_ptr<ConOp>>>();
        std::vector<ConLocation> no_args;
        std::vector<ConLocation> no_returns;
        condition_ops->push_back(std::make_shared<ConOpCall>(ConLocation(ConLocation::SECTION::REGS, ConRegs::LOCATION::REG_1), no_args, no_returns));

        ops->push_back(std::make_shared<ConOpCondition>(condition_ops));

        auto func = std::make_shared<ConFunction>(ops, init_data, 0, 1, 0);
        default_state_scope_functions->emplace(EVENT_FRAME_CALLBACK, func);
    }
    return std::make_shared<Scope>(std::make_shared<std::map<std::wstring, std::shared_ptr<ConFunction>>>(*default_state_scope_functions));
}

static std::map<size_t, std::shared_ptr<ConFunction>> handler_funcs;

enum class StateReset {
    STOP,
    RESTART,
    REMAIN,
};

static std::shared_ptr<ConFunction> get_handler_func(int new_state_index,
                                                     int frame_index,
                                                     int new_time,
                                                     bool is_time_relative,
                                                     StateReset state_reset) {
    auto func_ptr = handler_funcs.find(new_state_index);
    if (handler_funcs.end() == func_ptr) {
        std::vector<std::shared_ptr<RenderableState>> states;
        std::vector<std::any> init_data{};
        auto ops = std::make_shared<std::vector<std::shared_ptr<ConOp>>>();
        auto if_ops = std::make_shared<std::vector<std::shared_ptr<ConOp>>>();
        auto else_ops = std::make_shared<std::vector<std::shared_ptr<ConOp>>>();
        ops->push_back(std::make_shared<ConOpMove>(
                ConLocation(ConLocation::CONSTS, is_time_relative),
                ConLocation(ConLocation::REGS, ConRegs::CONDITION)
                ));

        if_ops->push_back(std::make_shared<ConOpEnterScope>(
                ConLocation(ConLocation::STACK, std::wstring(L"animation_logical"))
                ));
        if_ops->push_back(std::make_shared<ConOpMove>(
                ConLocation(ConLocation::STACK, std::wstring(L"time_in_frame")),
                ConLocation(ConLocation::REGS, ConRegs::REG_2)
                ));
        if_ops->push_back(std::make_shared<ConOpExitScope>(

                ));
        else_ops->push_back(std::make_shared<ConOpMove>(
                ConLocation(ConLocation::CONSTS, 0),
                ConLocation(ConLocation::REGS, ConRegs::REG_2)
                ));
        ops->push_back(std::make_shared<ConOpCondition>(if_ops, else_ops));

        ops->push_back(std::make_shared<ConOpEnterWeakScope>(
                ConLocation(ConLocation::STACK, std::wstring(L"parent_sprite"))
        ));

        ops->push_back(std::make_shared<ConOpEnterWeakScope>(
                ConLocation(ConLocation::STACK, std::wstring(L"parent_component"))
        ));
        ops->push_back(std::make_shared<ConOpMove>(
                ConLocation(ConLocation::STACK, std::wstring(L"current")),
                ConLocation(ConLocation::STACK, std::wstring(L"last_time"))
                ));
        ops->push_back(std::make_shared<ConOpMove>(
                ConLocation(ConLocation::STACK, std::wstring(L"last_time")),
                ConLocation(ConLocation::STACK, std::wstring(L"current"))
                ));
        ops->push_back(std::make_shared<ConOpExitScope>());

        ops->push_back(std::make_shared<ConOpMove>(
                ConLocation(ConLocation::CONSTS, new_state_index),
                ConLocation(ConLocation::STACK, std::wstring(L"current_state_index"))
        ));
        ops->push_back(std::make_shared<ConOpVectorGet>(
                ConLocation(ConLocation::STACK, std::wstring(L"states_logicals")),
                ConLocation(ConLocation::CONSTS, new_state_index),
                ConLocation(ConLocation::REGS, ConRegs::REG_1)
                ));
        ops->push_back(std::make_shared<ConOpEnterScope>(
                ConLocation(ConLocation::REGS, ConRegs::REG_1)
                ));
        ops->push_back(std::make_shared<ConOpEnterScope>(
                ConLocation(ConLocation::STACK, std::wstring(L"animation_logical"))
                ));
        ops->push_back(std::make_shared<ConOpMove>(
                ConLocation(ConLocation::CONSTS, frame_index),
                ConLocation(ConLocation::STACK, std::wstring(L"frame_index"))
                ));
        ops->push_back(std::make_shared<ConOpAdd>(
                ConLocation(ConLocation::REGS, ConRegs::REG_2),
                ConLocation(ConLocation::CONSTS, new_time),
                ConLocation(ConLocation::REGS, ConRegs::REG_2)
                ));
        ops->push_back(std::make_shared<ConOpMove>(
                ConLocation(ConLocation::REGS, ConRegs::REG_2),
                ConLocation(ConLocation::STACK, std::wstring(L"time_in_frame"))
                ));
        if (StateReset::REMAIN != state_reset) {
            ops->push_back(std::make_shared<ConOpMove>(
                    ConLocation(ConLocation::CONSTS, StateReset::RESTART == state_reset),
                    ConLocation(ConLocation::STACK, std::wstring(L"is_running"))
                    ));
        }
        auto func = std::make_shared<ConFunction>(ops, init_data, 0, 0, 0);
        handler_funcs[new_state_index] = func;
        return func;
    } else {
        return func_ptr->second;
    }
}

std::pair<size_t, bool> parse_relative_arg(const std::wstring& time_arg) {
    if (0 == time_arg.size()) {
        return {0, false};
    }
    std::wstring_view flag(time_arg.c_str(), 1);
    bool is_relative = L"R" == flag;
    if (!is_relative && L"A" != flag) {
        Logger::warn("Bad state handler time argument type, assuming absolute", {{"time_arg", string_converter.to_bytes(time_arg)}});
    }
    std::wstring_view number(time_arg.c_str() + 1, time_arg.size() - 1);
    return {StatesLoader1::parse_int(number, 0), is_relative};
}

StateReset parse_state_reset(const std::wstring& reset_arg) {
    if (reset_arg.empty()) {
        return StateReset::REMAIN;
    } else if (L"S" == reset_arg){
        return StateReset::STOP;
    } else if (L"R" == reset_arg) {
        return StateReset::RESTART;
    } else {
        Logger::warn("Bad state handler reset argument, assuming remain", {{"reset_arg", string_converter.to_bytes(reset_arg)}});
        return StateReset::REMAIN;
    }
}

std::shared_ptr<RenderableState> parse_state(const std::vector<std::wstring>& states_names,
                                             const std::shared_ptr<Animation>& animation,
                                             const std::map<std::wstring, std::tuple<std::wstring, std::wstring, std::wstring, std::wstring>>& handlers_args,
                                             const std::map<size_t, std::wstring>& callbacks_args) {
    auto new_state = std::make_shared<RenderableState>(std::dynamic_pointer_cast<Animation>(animation->copy()), get_default_state_scope());

    for (auto&[handler_name, handler_args] : handlers_args) {
        auto& [state_name, frame_index_arg, time_arg, reset_arg] = handler_args;
        auto state_index = std::find(states_names.begin(), states_names.end(), state_name);
        if (states_names.end() == state_index) {
            Logger::error("Failed to load handler", {{"state_name", string_converter.to_bytes(state_name)}});
            continue;
        }
        size_t frame_index = StatesLoader1::parse_int(frame_index_arg, 0);
        auto [time_offset, is_time_relative] = parse_relative_arg(time_arg);
        new_state->local_scope->functions->emplace(handler_name, get_handler_func(
                (int)(state_index - states_names.begin()),
                frame_index,
                time_offset,
                is_time_relative,
                parse_state_reset(reset_arg)
            ));
    }

    std::map<size_t, std::any> new_callbacks;
    for (auto&[frame_index, callback_name] : callbacks_args) {
        new_callbacks[frame_index] = callback_name;
    }
    SET_PTR(new_state, frame_callbacks, new_callbacks);

    return new_state;
}

void StatesLoader1::parse(std::wifstream& file_stream, size_t count, ParsedState& parsing_state) {
    std::vector<std::shared_ptr<RenderableState>> states;
    std::vector<std::wstring> state_names;

    auto animations = std::any_cast<std::map<size_t, std::shared_ptr<Animation>>>(*parsing_state.anims);

    auto start_state_line_res = StatesLoader1::parse_line(file_stream, START_STATE_REGEX);
    std::wstring start_line_name = start_state_line_res[0];

    std::vector<std::tuple<size_t, std::map<std::wstring, std::tuple<std::wstring, std::wstring, std::wstring, std::wstring>>, std::map<size_t, std::wstring>>> states_args;

    for (size_t i = 0; i < count; ++i) {
        auto state_name_line_res = StatesLoader1::parse_line(file_stream, NAME_REGEX);
        std::wstring state_name = state_name_line_res[0];

        auto animation_id_line_res = StatesLoader1::parse_line(file_stream, ANIMATION_REGEX);
        size_t animation_id = StatesLoader1::parse_int(animation_id_line_res[0]);

        auto handler_count_line_res = StatesLoader1::parse_line(file_stream, HANDLERS_COUNT_REGEX);
        size_t handler_count = StatesLoader1::parse_int(handler_count_line_res[0]);

        std::map<std::wstring, std::tuple<std::wstring, std::wstring, std::wstring, std::wstring>> handler_args;
        for (size_t j = 0; j < handler_count; ++j) {
            auto handler_line_res = StatesLoader1::parse_line(file_stream, HANDLER_REGEX);
            std::tuple<std::wstring, std::wstring, std::wstring, std::wstring> current_handler_args = {
                    handler_line_res[1],
                    handler_line_res[2],
                    handler_line_res[3],
                    handler_line_res[4],
            };
            handler_args[handler_line_res[0]] = current_handler_args;
        }

        auto callback_count_line_res = StatesLoader1::parse_line(file_stream, FRAME_CALLBACKS_COUNT_REGEX);
        size_t callback_count = StatesLoader1::parse_int(callback_count_line_res[0]);

        std::map<size_t, std::wstring> callbacks_args;
        for (size_t j = 0; j < callback_count; ++j) {
            auto handler_line_res = StatesLoader1::parse_line(file_stream, FRAME_CALLBACK_REGEX);
            callbacks_args[StatesLoader1::parse_int(handler_line_res[0])] = handler_line_res[1];
        }

        state_names.push_back(state_name);
        states_args.emplace_back(animation_id, handler_args, callbacks_args);
    }

    for (size_t i = 0; i < count; ++i) {
        const auto& [animation_id, handler_args, callbacks_args] = states_args.at(i);
        states.push_back(parse_state(state_names,
                                     animations[animation_id],
                                     handler_args,
                                     callbacks_args));
    }

    auto start_line_name_index = std::find(state_names.begin(), state_names.end(), start_line_name);
    if (state_names.end() == start_line_name_index) {
        Logger::error("Start state was not found");
        return;
    }
    std::pair<size_t, std::vector<std::shared_ptr<RenderableState>>> result = std::pair(start_line_name_index - state_names.begin(), states);
    parsing_state.states = std::make_unique<std::any>(result);
}
