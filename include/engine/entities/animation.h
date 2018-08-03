#ifndef ANIMATION_H
#define ANIMATION_H

#include "primitives/rectangle.h"
#include "engine/texture.h"

namespace engine
{

class Animation : public GraphicRectangle
{
public:
    Animation(const Bitmap* bitmap = nullptr);

    Animation(const Bitmap* bitmap, std::initializer_list<IntRect> frames);

    virtual ~Animation();

    const Bitmap* GetBitmap() const;

    const std::vector<IntRect>& GetFrames() const;

    int GetCurrentFrame() const;

    const Vector2<size_t>& GetFrameRange() const;

    bool IsRunning() const;

    bool IsLooped() const;

    float GetDelay() const;

    void SetBitmap(const Bitmap* bitmap);

    void SetFrames(std::initializer_list<IntRect> frames);

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

    virtual void Update(const float dt);

    virtual void Render(Renderer& renderer);

protected:
    const Bitmap*           m_bitmap;
    std::vector<IntRect>    m_frames;
    int                     m_current;
    Vector2<size_t>         m_frameRange;
    bool                    m_running;
    bool                    m_looped;
    float                   m_currentTime;
    float                   m_delay;
    int                     m_direction;
};

}

#endif // ANIMATION_H
