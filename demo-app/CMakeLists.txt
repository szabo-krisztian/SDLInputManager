add_library(DemoApp demo_app.cpp)
target_link_libraries(DemoApp
    PUBLIC
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    PRIVATE
    InputManager)
