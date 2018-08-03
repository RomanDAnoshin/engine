#include "engine/entities/animation.h"
using namespace engine;

Animation::Animation(const Bitmap* bitmap) :
    m_bitmap(bitmap),
    m_current(-1),
    m_frameRange(0, 0),
    m_running(false),
    m_looped(false),
    m_currentTime(0.f),
    m_delay(0.f),
    m_direction(1)
{

}

Animation::Animation(const Bitmap* bitmap, std::initializer_list<IntRect> frames) :
    Animation(bitmap)
{
    SetFrames(frames);
}

Animation::~Animation()
{

}

const Bitmap* Animation::GetBitmap() const
{
    return m_bitmap;
}

const std::vector<IntRect>& Animation::GetFrames() const
{
    return m_frames;
}

int Animation::GetCurrentFrame() const
{
    return m_current;
}

const Vector2<size_t>& Animation::GetFrameRange() const
{
    return m_frameRange;
}

bool Animation::IsRunning() const
{
    return m_running;
}

bool Animation::IsLooped() const
{
    return m_looped;
}

float Animation::GetDelay() const
{
    return m_delay;
}

void Animation::SetBitmap(const Bitmap* bitmap)
{
    m_bitmap = bitmap;
}

void Animation::SetFrames(std::initializer_list<IntRect> frames)
{
    m_frames = std::vector<IntRect>(frames);
    if (m_frames.empty()) {
        m_current = -1;
        m_frameRange = Vector2<size_t>(0, 0);
    } else {
        m_current = 0;
        SetFrameRange(m_frameRange);
    }
}

void Animation::AddFrame(const IntRect& frame)
{
    if (m_frames.empty()) {
        m_current = 0;
    }
    m_frames.push_back(frame);
}

void Animation::ClearFrames()
{
    m_frames.clear();
    m_frameRange = Vector2<size_t>(0, 0);
    m_current = -1;
}

void Animation::SetCurrentFrame(size_t frame)
{
    if (m_frames.empty()) {
        m_current = clamp(frame, size_t(0), m_frames.size() - 1);
    }
}

void Animation::SetFrameRange(size_t start, size_t finish)
{
    m_frameRange.x = clamp(start, size_t(0), m_frames.size() - 1);
    m_frameRange.y = clamp(finish, size_t(0), m_frames.size() - 1);
    m_direction = m_frameRange.x > m_frameRange.y ? -1 : 1;
}

void Animation::SetFrameRange(const Vector2<size_t>& range)
{
    SetFrameRange(range.x, range.y);
}

void Animation::SetLooped(bool looped)
{
    m_looped = looped;
}

void Animation::SetDelay(float delay)
{
    m_delay = delay;
}

void Animation::Play()
{
    if (m_frames.empty()) {
        return;
    }
    m_current = m_frameRange.x;
    m_running = m_frameRange.x != m_frameRange.y;
    m_currentTime = 0.f;
}

void Animation::Play(size_t start, size_t finish, float delay, bool loop)
{
    SetFrameRange(start, finish);
    SetDelay(delay);
    SetLooped(loop);
    Play();
}

void Animation::Stop()
{
    m_running = false;
}

void Animation::Update(const float dt)
{
    GraphicRectangle::Update(dt);
    if (m_running) {
        m_currentTime += dt;
        if (m_currentTime >= m_delay)
        {
            m_currentTime -= m_delay;
            m_current += m_direction;
            if (m_direction * m_current > m_direction * m_frameRange.y) {
                if (m_looped) {
                    m_current = m_frameRange.x;
                } else {
                    m_current = m_frameRange.y;
                    m_running = false;
                }
            }
        }
    }
}

void Animation::Render(Renderer& renderer)
{
    if (m_bitmap != nullptr && !m_frames.empty()) {
        prepareRenderer(renderer);
        renderer.DrawBitmap(m_bitmap, m_frames[m_current], FloatRect(m_center * -1.f, m_size), m_color);
    }
}
