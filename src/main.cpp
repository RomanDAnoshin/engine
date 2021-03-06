#include <iostream>
#include <functional>
#include "engine/engine.h"
using namespace engine;

int main(int argc, char *argv[])
{
    Engine engine;
    try {
        engine.Init();
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }

    EntityContainer& scene = engine.GetScene().GetRootEntity();
    WidgetContainer& gui = engine.GetScene().GetRootWidget();

    Bitmap backTexture("../resources/back.png");
    Sprite back(&backTexture);
    scene.AddEntity(&back);

    Bitmap face("../resources/face.png");
    Sprite s(&face);
    s.SetSize({64,64});
    s.SetCenter({32,32});
    s.SetColor(Color(0, 255, 0, 255));

    EntityContainer container;
    container.AddEntity(&s);
    container.SetPosition(100,100);
    scene.AddEntity(&container);

    SimpleText text("Houston, we have a problem");
    text.SetPosition(0, -48);
    text.SetAlign(HAlignment::Center, VAlignment::Top);
    container.AddEntity(&text);

    PointParticleEmitter particle;
    particle.SetBitmap(&face);
    particle.SetRandomAngle(Angle::FromDegrees(75), Angle::FromDegrees(105));
    particle.SetPosition(0, 32);
    ParticleParameters params;
    params.startColorRange = Color(255, 64, 0);
    params.finishColorRange = Color(128, 0, 0, 64);
    params.delayRange = 0.02f;
    particle.SetParameters(params);
    container.AddEntity(&particle, 0);

    GraphicRectangle rect1;
    rect1.SetSize(Vector2f(32, 16));
    rect1.SetPosition(-48, 0);
    rect1.SetCenter(Vector2f(16,8));
    rect1.SetColor(Color(64,128,211));

    GraphicRectangle rect2;
    rect2.SetSize(Vector2f(32, 16));
    rect2.SetPosition(48, 0);
    rect2.SetCenter(Vector2f(16,8));
    rect2.SetColor(Color(64,128,211));

    GraphicPolygon poly;
    poly.SetVertices({Vector2f(-8, 0), Vector2f(-16, 32), Vector2f(16, 32), Vector2f(8, 0)});
    poly.SetPosition(0, 18);
    poly.SetColor(Color(243,124,55));
    container.AddEntity(&poly, 1);

    container.AddEntity(&rect1);
    container.AddEntity(&rect2);

    b2Vec2 grav(0.f, 0.f);
    b2World* world = new b2World(grav);

    b2BodyDef def1;
    def1.position.SetZero();
    def1.position.Set(0/30.f, 0/30.f);
    def1.type = b2_dynamicBody;
    b2Body* b1 = world->CreateBody(&def1);
    b2CircleShape circle;
    circle.m_radius = 30/30.0;
    b2FixtureDef circledef;
    circledef.shape = &circle;
    circledef.density = 1.0;
    circledef.friction = 0.3;
    b1->CreateFixture(&circledef);
    b1->SetUserData(&container);

    GraphicRectangle rect;
    rect.SetPosition(400,300);
    rect.SetSize(Vector2f(64,128));
    rect.SetCenter(Vector2f(32,64));
    rect.SetColor(Color(32,32,255));
    rect.SetBorderStyle(BorderStyle(Color(0,0,0), 10));
    scene.AddEntity(&rect);

    b2BodyDef def2;
    def2.position.Set(400/30.0, 300/30.0);
    def2.type = b2_staticBody;
    b2Body* b2 = world->CreateBody(&def2);
    b2PolygonShape polygon;
    polygon.SetAsBox(32 / 30.f, 64/30.f);
    b2FixtureDef polygondef;
    polygondef.shape = &polygon;
    polygondef.density = 1.0;
    polygondef.friction = 0.3;
    b2->CreateFixture(&polygondef);
    b2->SetUserData(&rect);

    Physics_Box2D physics;
    physics.SetWorld(world);
    engine.GetScene().SetPhysics(&physics);

    Font f("../resources/ArialCyrRegular.ttf", 20);

    Label label;
    label.SetFont(f);
    label.SetBackColor(Color(128,128,128));
    label.SetBounds(0, 500, 800, 100);
    label.SetHorizontalAlign(HAlignment::Left);
    label.SetVerticalAlign(VAlignment::Top);
    label.SetAnchor(Anchor::All);
    label.SetMultiline(true);
    label.SetLineSpacing(4);
    label.SetText(
                "Vincent: And you know what they call a... a... a Quarter Pounder with Cheese in Paris?\n"
                "Jules: They don't call it a Quarter Pounder with cheese?\n"
                "Vincent: No man, they got the metric system. They wouldn't know what the fuck a Quarter Pounder is.\n"
                "Jules: Then what do they call it?\n"
                "Vincent: They call it a Royale with cheese.\n"
                "Jules: A Royale with cheese. What do they call a Big Mac?\n"
                "Vincent: Well, a Big Mac's a Big Mac, but they call it le Big-Mac.\n"
                );
    gui.AddWidget(&label);


    float angle = 0;
    float speed = 250.f;
    Button button("Reset");
    button.SetPosition(800 - button.GetSize().x, 0);
    button.EventClick().ConnectStdFunction([b1, &particle, &angle]() {
        angle = 0;
        particle.SetMaxParticleCount(0);
        b1->SetTransform(b2Vec2(5, 5), angle);
        b1->SetLinearVelocity(b2Vec2_zero);
        b1->SetAngularVelocity(0);
    });
    button.EventMouseEnter().ConnectStdFunction([&engine, &button]() {
        engine.SetSystemCursor(SYSTEM_CURSOR::SYSTEM_CURSOR_LINK);
        button.SetBackColor(Color(192, 192, 255));
    });
    button.EventMouseLeave().ConnectStdFunction([&engine, &button]() {
        engine.SetSystemCursor(SYSTEM_CURSOR::SYSTEM_CURSOR_ARROW);
        button.SetBackColor(Color(192, 192, 192));
    });

    gui.AddWidget(&button);

    auto lerp = make_lerp(button.GetProperty(&Button::GetPosition, &Button::SetPosition),
                          Vector2f(button.GetPosition().x, 600 - button.GetSize().y), 10.f);
    lerp->EventFinished().ConnectStdFunction([&button]() {
        auto lerp1 = make_lerp(button.GetProperty(&Button::GetPosition, &Button::SetPosition),
                              Vector2f(button.GetPosition().x, 0), 10.f);
        button.AddTask(lerp1);
    });
    button.AddTask(lerp);

//    poly.AddTask(make_lerp(poly.GetProperty(&GraphicPolygon::GetPosition, &GraphicPolygon::SetPosition),
//                           Vector2f(0, 300), 10.f));

//    button.AddTask(make_lerp(button.GetProperty(&Button::GetPosition, &Button::SetPosition),
//                             Vector2i(0, 0), Vector2i(600,400), 10.f));
//    button.AddTask(make_lerp(button.GetProperty(&Button::GetSize, &Button::SetSize),
//                             Vector2i(32, 32), Vector2i(600,400), 10.f));


    Bitmap oldmanBitmap("../resources/oldman.png");
    FrameAnimation oldman(&oldmanBitmap);
    oldman.SetPosition(500, 100);
    oldman.SetSize(64,64);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 9; ++j)
            oldman.AddFrame(IntRect(j * 64, i * 64, 64, 64));
    oldman.Play(9, 17, 0.1f, true);
    scene.AddEntity(&oldman);

    engine.EventUpdating().ConnectStdFunction([&engine, &b1, &container, &particle, &angle, &speed](const float dt) {
        float value = speed * dt;
        if (Input::IsKeyPressed(KEYBOARD::W))
            particle.SetMaxParticleCount(particle.GetMaxParticleCount() + 1);
        if (Input::IsKeyPressed(KEYBOARD::S))
            particle.SetMaxParticleCount(particle.GetMaxParticleCount() - 1);
        speed = particle.GetAliveParticleCount() * 10.f;
        if (Input::IsKeyPressed(KEYBOARD::A))
            angle -= 2.f * dt;
        if (Input::IsKeyPressed(KEYBOARD::D))
            angle += 2.f * dt;
        b1->SetTransform(b1->GetPosition(), angle);
        b2Vec2 force(std::sin(angle) * value, -1.f * std::cos(angle) * value);
        if (force.x != 0 || force.y != 0)
            b1->ApplyForce(force, b1->GetPosition(), true);
    });

    engine.Start();
    scene.Clear();
    engine.Cleanup();
    return 0;
}
