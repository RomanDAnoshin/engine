cmake_minimum_required(VERSION 2.6)
project(engine)
set(CMAKE_CXX_STANDARD 11)

set(SOURCES
    main.cpp
    src/engine.cpp
    src/texture.cpp
    src/physics.cpp
    src/input.cpp
    src/cursor.cpp
    src/scene.cpp
    src/renderer.cpp
    src/transform.cpp
    src/text/text.cpp
    src/text/font.cpp
    src/entities/entity.cpp
    src/entities/simpletext.cpp
    src/entities/sprite.cpp
    src/entities/particles.cpp
    src/entities/entitycontainer.cpp
    src/entities/primitives/primitive.cpp
    src/entities/primitives/rectangle.cpp
    src/entities/primitives/ellipse.cpp
    src/entities/primitives/polygon.cpp
    src/widgets/widget.cpp
    src/widgets/label.cpp
    src/widgets/widgetcontainer.cpp
    src/widgets/button.cpp
    src/widgets/mousearea.cpp
    src/object.cpp
)

set(HEADERS
    include/engine.h
    include/globals.h
    include/texture.h
    include/physics.h
    include/input.h
    include/event.h
    include/cursor.h
    include/scene.h
    include/renderer.h
    include/transform.h
    include/text/text.h
    include/text/font.h
    include/entities/entity.h
    include/entities/simpletext.h
    include/entities/sprite.h
    include/entities/particles.h
    include/entities/entitycontainer.h
    include/entities/primitives/primitives.h
    include/entities/primitives/primitive.h
    include/entities/primitives/rectangle.h
    include/entities/primitives/ellipse.h
    include/entities/primitives/polygon.h
    include/widgets/widget.h
    include/widgets/label.h
    include/widgets/widgetcontainer.h
    include/widgets/button.h
    include/widgets/mousearea.h
    include/object.h
)

set(LIBS
    allegro_monolith.dll
    Box2D
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${LIBS})
