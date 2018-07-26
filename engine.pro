CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

VPATH += $$PWD/engine
INCLUDEPATH += $$PWD/engine

LIBS += -L$$PWD/libs/allegro/lib -lallegro_monolith.dll
INCLUDEPATH += $$PWD/libs/allegro/include

INCLUDEPATH += $$PWD/libs/Box2D/include
LIBS += -L$$PWD/libs/Box2D/lib -lBox2D

SOURCES += \
    main.cpp \
    engine/engine.cpp \
    engine/texture.cpp \
    engine/physics.cpp \
    engine/input.cpp \
    engine/cursor.cpp \
    engine/scene.cpp \
    engine/renderer.cpp \
    engine/transform.cpp \
    engine/text/text.cpp \
    engine/text/font.cpp \
    engine/entities/entity.cpp \
    engine/entities/simpletext.cpp \
    engine/entities/sprite.cpp \
    engine/entities/particles.cpp \
    engine/entities/entitycontainer.cpp \
    engine/entities/primitives/primitive.cpp \
    engine/entities/primitives/rectangle.cpp \
    engine/entities/primitives/ellipse.cpp \
    engine/entities/primitives/polygon.cpp \
    engine/widgets/widget.cpp \
    engine/widgets/label.cpp \
    engine/widgets/widgetcontainer.cpp \
    engine/widgets/button.cpp \
    engine/widgets/mousearea.cpp \
    engine/object.cpp


HEADERS += \
    engine/engine.h \
    engine/globals.h \
    engine/texture.h \
    engine/physics.h \
    engine/input.h \
    engine/event.h \
    engine/cursor.h \
    engine/scene.h \
    engine/renderer.h \
    engine/transform.h \
    engine/text/text.h \
    engine/text/font.h \
    engine/entities/entity.h \
    engine/entities/simpletext.h \
    engine/entities/sprite.h \
    engine/entities/particles.h \
    engine/entities/entitycontainer.h \
    engine/entities/primitives/primitives.h \
    engine/entities/primitives/primitive.h \
    engine/entities/primitives/rectangle.h \
    engine/entities/primitives/ellipse.h \
    engine/entities/primitives/polygon.h \
    engine/widgets/widget.h \
    engine/widgets/label.h \
    engine/widgets/widgetcontainer.h \
    engine/widgets/button.h \
    engine/widgets/mousearea.h \
    engine/object.h
