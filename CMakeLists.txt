cmake_minimum_required(VERSION 2.6)
project(engine)
set(CMAKE_CXX_STANDARD 11)

set(SOURCES
    main.cpp
    engine/engine.cpp
    engine/texture.cpp
    engine/physics.cpp
    engine/input.cpp
    engine/cursor.cpp
    engine/scene.cpp
    engine/renderer.cpp
    engine/transform.cpp
    engine/text/text.cpp
    engine/text/font.cpp
    engine/entities/entity.cpp
    engine/entities/simpletext.cpp
    engine/entities/sprite.cpp
    engine/entities/particles.cpp
    engine/entities/entitycontainer.cpp
    engine/entities/primitives/primitive.cpp
    engine/entities/primitives/rectangle.cpp
    engine/entities/primitives/ellipse.cpp
    engine/entities/primitives/polygon.cpp
    engine/widgets/widget.cpp
    engine/widgets/label.cpp
    engine/widgets/widgetcontainer.cpp
    engine/widgets/button.cpp
    engine/widgets/mousearea.cpp
    engine/object.cpp
)

set(HEADERS
    engine/engine.h
    engine/globals.h
    engine/texture.h
    engine/physics.h
    engine/input.h
    engine/event.h
    engine/cursor.h
    engine/scene.h
    engine/renderer.h
    engine/transform.h
    engine/text/text.h
    engine/text/font.h
    engine/entities/entity.h
    engine/entities/simpletext.h
    engine/entities/sprite.h
    engine/entities/particles.h
    engine/entities/entitycontainer.h
    engine/entities/primitives/primitives.h
    engine/entities/primitives/primitive.h
    engine/entities/primitives/rectangle.h
    engine/entities/primitives/ellipse.h
    engine/entities/primitives/polygon.h
    engine/widgets/widget.h
    engine/widgets/label.h
    engine/widgets/widgetcontainer.h
    engine/widgets/button.h
    engine/widgets/mousearea.h
    engine/object.h
)

set(LIBS
    allegro_monolith.dll
    Box2D
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/allegro/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/Box2D/include
    ${CMAKE_CURRENT_SOURCE_DIR}/engine
)

link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/allegro/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/Box2D/lib
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${LIBS})
