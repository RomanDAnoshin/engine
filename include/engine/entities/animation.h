#ifndef ANIMATION_H
#define ANIMATION_H

#include "engine/common/math.h"
#include "primitives/rectangle.h"
#include "engine/texture.h"

namespace engine
{

class FrameAnimation : public GraphicRectangle
{
public:
    FrameAnimation(const Bitmap* bitmap = nullptr);

    FrameAnimation(const Bitmap* bitmap, std::initializer_list<IntRect> frames);

    const Bitmap* GetBitmap() const;

    const std::vector<IntRect>& GetFrames() const;

    int GetCurrentFrame() const;

    const Vector2<size_t>& GetFrameRange() const;

    bool IsRunning() const;

    bool IsLooped() const;

    float GetDelay() const;

    void SetBitmap(const Bitmap* bitmap);

    void SetFrames(std::initializer_list<IntRect> frames);

    void SetFrames(const std::vector<IntRect>& frames);

    void AddFrame(const IntRect& frame);

    void ClearFrames();

    void SetCurrentFrame(size_t frame);

    void SetFrameRange(size_t start, size_t finish);

    void SetFrameRange(const Vector2<size_t>& range);

    void SetLooped(bool looped);

    void SetDelay(float delay);

    void Play();

    void Play(size_t start, size_t finish, float delay, bool loop = false);

    void Stop();

    void Update(const float dt);

    void Render(Renderer& renderer);

protected:
    std::vector<IntRect>    m_frames;
    Vector2<size_t>         m_frameRange;
    const Bitmap*           m_bitmap;
    float                   m_currentTime;
    float                   m_delay;
    int                     m_current;
    int                     m_direction;
    bool                    m_running;
    bool                    m_looped;
};

}

#endif // ANIMATION_H
