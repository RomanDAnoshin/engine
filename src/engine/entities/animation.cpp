#include "engine/entities/animation.h"
using namespace engine;

FrameAnimation::FrameAnimation(const Bitmap* bitmap) :
    m_frameRange(0, 0),
    m_bitmap(bitmap),
    m_currentTime(0.f),
    m_delay(0.f),
    m_current(-1),
    m_direction(1),
    m_running(false),
    m_looped(false)
{

}

FrameAnimation::FrameAnimation(const Bitmap* bitmap, std::initializer_list<IntRect> frames) :
    FrameAnimation(bitmap)
{
    SetFrames(frames);
}

const Bitmap* FrameAnimation::GetBitmap() const
{
    return m_bitmap;
}

const std::vector<IntRect>& FrameAnimation::GetFrames() const
{
    return m_frames;
}

int FrameAnimation::GetCurrentFrame() const
{
    return m_current;
}

const Vector2<size_t>& FrameAnimation::GetFrameRange() const
{
    return m_frameRange;
}

bool FrameAnimation::IsRunning() const
{
    return m_running;
}

bool FrameAnimation::IsLooped() const
{
    return m_looped;
}

float FrameAnimation::GetDelay() const
{
    return m_delay;
}

void FrameAnimation::SetBitmap(const Bitmap* bitmap)
{
    m_bitmap = bitmap;
}

void FrameAnimation::SetFrames(std::initializer_list<IntRect> frames)
{
    m_frames = std::vector<IntRect>(frames);
    if (m_frames.empty()) {
        SetFrameRange(0, 0);
    } else {
        SetFrameRange(m_frameRange);
    }
}

void FrameAnimation::SetFrames(const std::vector<IntRect>& frames)
{
    m_frames = std::vector<IntRect>(frames);
    if (m_frames.empty()) {
        SetFrameRange(0, 0);
    } else {
        SetFrameRange(m_frameRange);
    }
}

void FrameAnimation::AddFrame(const IntRect& frame)
{
    m_frames.push_back(frame);
}

void FrameAnimation::ClearFrames()
{
    m_frames.clear();
    m_frameRange = Vector2<size_t>(0, 0);
    m_current = -1;
}

void FrameAnimation::SetCurrentFrame(size_t frame)
{
    if (m_frames.empty()) {
        m_current = math::clamp(frame, m_frameRange.x, m_frameRange.y);
    }
}

void FrameAnimation::SetFrameRange(size_t start, size_t finish)
{
    m_frameRange.x = math::clamp(start, size_t(0), m_frames.size() - 1);
    m_frameRange.y = math::clamp(finish, size_t(0), m_frames.size() - 1);
    m_current = m_frames.empty() ? -1 : math::clamp(size_t(m_current), m_frameRange.x, m_frameRange.y);
    m_direction = m_frameRange.x > m_frameRange.y ? -1 : 1;
}

void FrameAnimation::SetFrameRange(const Vector2<size_t>& range)
{
    SetFrameRange(range.x, range.y);
}

void FrameAnimation::SetLooped(bool looped)
{
    m_looped = looped;
}

void FrameAnimation::SetDelay(float delay)
{
    m_delay = delay;
}

void FrameAnimation::Play()
{
    if (m_frames.empty()) {
        return;
    }
    m_current = m_frameRange.x;
    m_running = m_frameRange.x != m_frameRange.y;
    m_currentTime = 0.f;
}

void FrameAnimation::Play(size_t start, size_t finish, float delay, bool loop)
{
    SetFrameRange(start, finish);
    SetDelay(delay);
    SetLooped(loop);
    Play();
}

void FrameAnimation::Stop()
{
    m_running = false;
}

void FrameAnimation::Update(const float dt)
{
    GraphicRectangle::Update(dt);
    if (m_running) {
        m_currentTime += dt;
        while (m_currentTime >= m_delay)
        {
            m_currentTime -= m_delay;
            m_current += m_direction;
            if (m_direction < 0 && m_current < m_frameRange.y ||
                m_direction > 0 && m_current > m_frameRange.y) {
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

void FrameAnimation::Render(Renderer& renderer)
{
    if (m_bitmap != nullptr && !m_frames.empty()) {
        prepareRenderer(renderer);
        renderer.DrawBitmap(m_bitmap, m_frames[m_current], FloatRect(m_center * -1.f, m_size), m_color);
    }
}
