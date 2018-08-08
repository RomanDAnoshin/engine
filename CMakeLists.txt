cmake_minimum_required(VERSION 2.6)
project(engine)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SOURCES
    src/main.cpp
    src/engine/engine.cpp
    src/engine/texture.cpp
    src/engine/physics.cpp
    src/engine/input.cpp
    src/engine/cursor.cpp
    src/engine/scene.cpp
    src/engine/renderer.cpp
    src/engine/transform.cpp
    src/engine/common/math.cpp
    src/engine/common/angle.cpp
    src/engine/common/color.cpp
    src/engine/common/borderstyle.cpp
    src/engine/common/vertex.cpp
    src/engine/text/text.cpp
    src/engine/text/font.cpp
    src/engine/entities/entity.cpp
    src/engine/entities/simpletext.cpp
    src/engine/entities/sprite.cpp
    src/engine/entities/particles.cpp
    src/engine/entities/entitycontainer.cpp
    src/engine/entities/animation.cpp
    src/engine/entities/primitives/primitive.cpp
    src/engine/entities/primitives/rectangle.cpp
    src/engine/entities/primitives/ellipse.cpp
    src/engine/entities/primitives/polygon.cpp
    src/engine/widgets/widget.cpp
    src/engine/widgets/label.cpp
    src/engine/widgets/widgetcontainer.cpp
    src/engine/widgets/button.cpp
    src/engine/widgets/mousearea.cpp
    src/engine/object.cpp
)

set(HEADERS
    include/engine/engine.h
    include/engine/texture.h
    include/engine/physics.h
    include/engine/input.h
    include/engine/cursor.h
    include/engine/scene.h
    include/engine/renderer.h
    include/engine/transform.h
    include/engine/common/math.h
    include/engine/common/angle.h
    include/engine/common/vector2.h
    include/engine/common/vector3.h
    include/engine/common/rect.h
    include/engine/common/color.h
    include/engine/common/borderstyle.h
    include/engine/common/vertex.h
    include/engine/common/delegate.h
    include/engine/common/event.h
    include/engine/common/property.h
    include/engine/text/text.h
    include/engine/text/font.h
    include/engine/entities/entity.h
    include/engine/entities/simpletext.h
    include/engine/entities/sprite.h
    include/engine/entities/particles.h
    include/engine/entities/entitycontainer.h
    include/engine/entities/animation.h
    include/engine/entities/primitives/primitives.h
    include/engine/entities/primitives/primitive.h
    include/engine/entities/primitives/rectangle.h
    include/engine/entities/primitives/ellipse.h
    include/engine/entities/primitives/polygon.h
    include/engine/widgets/widget.h
    include/engine/widgets/label.h
    include/engine/widgets/widgetcontainer.h
    include/engine/widgets/button.h
    include/engine/widgets/mousearea.h
    include/engine/object.h
    include/engine/tasks/task.h
    include/engine/tasks/timer.h
    include/engine/tasks/interpolation.h
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
