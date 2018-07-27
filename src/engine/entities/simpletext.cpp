#include "engine/entities/simpletext.h"
using namespace engine;

SimpleText::SimpleText(const std::string& text, const Font& font) :
    Entity(),
    Text(text, font)
{

}

void SimpleText::Update(const float dt)
{
    Entity::Update(dt);
}

void SimpleText::Render(Renderer& renderer)
{
    prepareRenderer(renderer);
    renderer.DrawText(m_font, m_text, m_point, m_alignH, m_textColor);
}
