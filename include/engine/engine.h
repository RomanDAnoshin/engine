#ifndef ENGINE_H
#define ENGINE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include <iostream>
#include <stdexcept>
#include <ctime>
#include "texture.h"
#include "renderer.h"
#include "physics.h"
#include "input.h"
#include "tools/event.h"
#include "text/text.h"
#include "cursor.h"

#include "scene.h"

#include "entities/entitycontainer.h"
#include "entities/sprite.h"
#include "entities/particles.h"
#include "entities/simpletext.h"
#include "entities/primitives/primitives.h"

#include "widgets/widget.h"
#include "widgets/widgetcontainer.h"
#include "widgets/label.h"
#include "widgets/button.h"

#include "tools/interpolation.h"

namespace engine
{

class Engine
{
public:
    Engine();

    ~Engine();

    Input& GetInput();

    Scene& GetScene();

    bool SetCursor(const Cursor& cursor);

    bool SetSystemCursor(SYSTEM_CURSOR cursor);

    void Start();

    void Cleanup();

    void Init();

    void Stop();

    //events
    Event<const float>& EventUpdating();

    Event<Renderer&>& EventRendering();

    Event<ALLEGRO_EVENT&> EventHandlingEvent();

private:
    void update();

    void render();

    void handleEvent(ALLEGRO_EVENT& event);

    int     m_width;
    int     m_height;
    float   m_dt;
    float   m_factor;
    bool    m_active;
    bool    m_running;

    Renderer                m_renderer;

    ALLEGRO_DISPLAY*        m_display;
    ALLEGRO_EVENT_QUEUE*    m_eventQueue;

    ALLEGRO_TIMER*  m_updateTimer;
    ALLEGRO_TIMER*  m_renderTimer;
    int             m_fps;
    int             m_ups;
    bool            m_needUpdate;
    bool            m_needRender;
    Input           m_input;

    Scene   m_scene;

    const Cursor*   m_cursor;

    Event<const float>      m_updating;
    Event<Renderer&>        m_rendering;
    Event<ALLEGRO_EVENT&>   m_handlingEvent;
};

}

#endif // ENGINE_H
