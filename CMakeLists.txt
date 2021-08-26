cmake_minimum_required(VERSION 3.20)
project(TerraMinal)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)

set(con_ops_sources con_script/ops/control/ConMove.cpp con_script/ops/control/ConCondition.cpp
        con_script/ops/scope/ConExistVar.cpp con_script/ops/scope/ConEnterScope.cpp
        con_script/ops/scope/ConExitScope.cpp con_script/ops/vector/ConVectorGet.cpp
        con_script/ops/vector/ConVectorSet.cpp con_script/ops/cpp/ConFunc.cpp
        con_script/ops/scope/ConEnterWeakScope.cpp con_script/ops/int_map/ConIntMapGet.cpp
        con_script/ops/int_map/ConIntMapSet.cpp con_script/ops/control/ConCall.cpp con_script/ops/ConOp.cpp
        con_script/ops/ConOpType.cpp con_script/ops/int/ConOpAdd.cpp)

set(con_script_sources con_script/data/Scope.h con_script/data/Stack.h con_script/data/Stack.cpp
        con_script/ConLocation.cpp ${con_ops_sources} con_script/ConFunction.cpp)

set(chars_loader_sources loader/SpriteLoader/CharsLoader/CharsLoader1.cpp)
set(attrs_loader_sources loader/SpriteLoader/AttrsLoader/AttrsLoader1.cpp)
set(frames_loader_sources loader/SpriteLoader/FramesLoader/FramesLoader1.cpp)
set(animations_loader_sources loader/SpriteLoader/AnimationsLoader/AnimationsLoader1.cpp)
set(states_loader_sources loader/SpriteLoader/StatesLoader/StatesLoader1.cpp)

set(sprite_loader_sources loader/SpriteLoader/SpriteLoader.cpp loader/SpriteLoader/SpriteLoader1.cpp
        loader/SpriteLoader/SubLoaderBase.cpp ${chars_loader_sources} ${attrs_loader_sources} ${frames_loader_sources}
        ${animations_loader_sources} ${states_loader_sources})
set(loader_sources loader/Loader.cpp ${sprite_loader_sources})

set(renderable_sources renderable/Animation.cpp renderable/RenderableState.cpp renderable/Frame.cpp renderable/Sprite.cpp con_script/Logical.h)
set(components_sources components/Component.cpp components/Scene.cpp)

set(logger_sources logger/Logger.cpp logger/log_filter/TrueLogFilter.cpp logger/log_filter/LambdaLogFilter.cpp
        logger/log_formatter/LineLogFormatter.cpp logger/log_writer/FileLogWriter.cpp)

set(engine_sources engine/Screen.cpp engine/Engine.cpp engine/World.cpp con_script/ConLocation.cpp ${logger_sources} utils/string_converter.h exceptions/con_script/stack_exception.h utils/IdGenerator.h)

include_directories(.)

add_executable(TerraMinal main.cpp ${engine_sources} ${renderable_sources} ${con_script_sources} ${components_sources}
        ${loader_sources})
target_link_libraries(TerraMinal -static-libgcc -static-libstdc++)
