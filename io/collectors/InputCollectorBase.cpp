#include "InputCollectorBase.h"

InputCollectorBase::InputCollectorBase(std::weak_ptr<InputManager> input_manager) : input_manager(std::move(input_manager)) {}
