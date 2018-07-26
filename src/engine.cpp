#include "engine.h"
using namespace engine;

Engine::Engine() :
    m_width(800),
    m_height(600),
    m_dt(0),
    m_factor(0),
    m_active(false),
    m_running(false),
    m_display(nullptr),
    m_eventQueue(nullptr),
    m_updateTimer(nullptr),
    m_renderTimer(nullptr),
    m_fps(30),
    m_ups(30),
    m_needUpdate(false),
    m_needRender(false),
    m_cursor(nullptr)
{

}

Engine::~Engine()
{
    Cleanup();
}

Input& Engine::GetInput()
{
    return m_input;
}

Scene& Engine::GetScene()
{
    return m_scene;
}

bool Engine::SetCursor(const Cursor& cursor)
{
    ALLEGRO_MOUSE_CURSOR* handle = const_cast<ALLEGRO_MOUSE_CURSOR*>(cursor.GetCursorHandle());
    if (handle == nullptr)
        return false;
    m_cursor = &cursor;
    return al_set_mouse_cursor(m_display, handle);
}

bool Engine::SetSystemCursor(SYSTEM_CURSOR cursor)
{
    m_cursor = nullptr;
    return al_set_system_mouse_cursor(m_display, (ALLEGRO_SYSTEM_MOUSE_CURSOR)cursor);
}

void Engine::Start()
{
    m_running = true;
    m_active = true;

    m_dt = 1.f / m_ups;

    al_start_timer(m_updateTimer);
    al_start_timer(m_renderTimer);

    while (m_running) {

        ALLEGRO_EVENT e;

        while (al_get_next_event(m_eventQueue, &e))
            handleEvent(e);

        if (m_needUpdate) {
            m_needUpdate = false;
            update();
        }
        if (m_needRender) {
            m_needRender = false;
            render();
        }
        al_rest(0.001);
    }
}

void Engine::Cleanup()
{
    if (al_is_keyboard_installed()) {
        al_uninstall_keyboard();
    }
    if (al_is_mouse_installed()) {
        al_uninstall_mouse();
    }
    if (m_eventQueue != nullptr) {
        al_destroy_event_queue(m_eventQueue);
        m_eventQueue = nullptr;
    }
    if (m_display != nullptr) {
        al_destroy_display(m_display);
        m_display = nullptr;
    }
}

void Engine::Init()
{
    std::srand(std::time(0));

    if (!al_init())
        throw std::runtime_error("Failed to initialize allegro\n");

    if (!al_init_image_addon())
        throw std::runtime_error("Failed to initialize image addon\n");

    if (!al_init_primitives_addon())
        throw std::runtime_error("Failed to initialize primitives addon\n");

    if (!al_init_font_addon())
        throw std::runtime_error("Failed to initialize font addon\n");

    if (!al_init_ttf_addon())
        throw std::runtime_error("Failed to initialize ttf addon\n");

    //al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_REQUIRE);
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    m_display = al_create_display(m_width, m_height);
    if (m_display == nullptr)
        throw std::runtime_error("Failed to create display\n");

    m_updateTimer = al_create_timer(1.0 / m_ups);
    if (m_updateTimer == nullptr)
        throw std::runtime_error("Failed to create update timer\n");

    m_renderTimer = al_create_timer(1.0 / m_fps);
    if (m_renderTimer == nullptr)
        throw std::runtime_error("Failed to create render timer\n");

    if (!al_install_keyboard())
        throw std::runtime_error("Failed to initialize keyboard\n");

    if (!al_install_mouse())
        throw std::runtime_error("Failed to initialize mouse\n");

    m_eventQueue = al_create_event_queue();
    if (m_eventQueue == nullptr)
        throw std::runtime_error("Failed to create event queue\n");

    al_register_event_source(m_eventQueue, al_get_display_event_source(m_display));
    al_register_event_source(m_eventQueue, al_get_timer_event_source(m_updateTimer));
    al_register_event_source(m_eventQueue, al_get_timer_event_source(m_renderTimer));
    al_register_event_source(m_eventQueue, al_get_keyboard_event_source());
    al_register_event_source(m_eventQueue, al_get_mouse_event_source());
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

    m_scene.GetRootWidget().SetSize(m_width, m_height);
}

void Engine::Stop()
{
    m_running = false;
}

Event<const float>& Engine::EventUpdating()
{
    return m_updating;
}

Event<Renderer&>& Engine::EventRendering()
{
    return m_rendering;
}

Event<ALLEGRO_EVENT&> Engine::EventHandlingEvent()
{
    return m_handlingEvent;
}

void Engine::update()
{
    m_scene.Update(m_dt);
    m_updating.Invoke(m_dt);
}

void Engine::render()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));

    m_scene.Render(m_renderer);

    m_rendering.Invoke(m_renderer);
    al_flip_display();
}

void Engine::handleEvent(ALLEGRO_EVENT& event)
{
    m_input.HandleEvent(event);
    m_scene.HandleEvent(event);

    switch (event.type) {
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
        m_running = false;
        break;

    case ALLEGRO_EVENT_TIMER:
        if (event.timer.source == m_updateTimer)
            m_needUpdate = true;
        else if (event.timer.source == m_renderTimer)
            m_needRender = true;
        break;

    case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
        m_active = true;
        al_resume_timer(m_updateTimer);
        al_resume_timer(m_renderTimer);
        break;
    case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
        m_active = false;
        al_stop_timer(m_updateTimer);
        al_stop_timer(m_renderTimer);
        break;
    case ALLEGRO_EVENT_DISPLAY_RESIZE: {
        al_acknowledge_resize(m_display);
        m_width = al_get_display_width(m_display);
        m_height = al_get_display_height(m_display);
        m_scene.GetRootWidget().SetBounds(0, 0, m_width, m_height);
        break;
    }
    default:
        break;
    }

    m_handlingEvent.Invoke(event);
}
