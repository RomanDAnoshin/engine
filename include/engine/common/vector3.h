#ifndef VECTOR3_H
#define VECTOR3_H

namespace engine
{

template <typename T>
struct Vector3
{
    Vector3() :
        Vector3(T(), T(), T())
    {

    }

    Vector3(const T& x, const T& y, const T& z) :
        x(x),
        y(y),
        z(z)
    {

    }

    Vector3(const T& value) :
        Vector3(value, value, value)
    {

    }

    void Sort()
    {
        if (x > y){
            T t = x;
            x = y;
            y = t;
        }
        if (x > c){
            T t = x;
            x = c;
            c = t;
        }
        if (y > z){
            T t = y;
            y = z;
            z = t;
        }
    }

    template <typename U>
    operator Vector3<U>() const
    {
        return Vector3<U>(static_cast<U>(x), static_cast<U>(y), static_cast<U>(z));
    }

    Vector3<T> operator+(const Vector3<T>& r) const
    {
        const Vector3& l = *this;
        return Vector3<T>(l.x + r.x, l.y + r.y, l.z + r.z);
    }

    Vector3<T> operator-(const Vector3<T>& r) const
    {
        const Vector3& l = *this;
        return Vector3<T>(l.x - r.x, l.y - r.y, l.z - r.z);
    }

    Vector3<T> operator*(float r) const
    {
        const Vector3& l = *this;
        return Vector3<T>(l.x * r, l.y * r, l.z * r);
    }

    Vector3<T> operator/(float r) const
    {
        const Vector3& l = *this;
        return Vector3<T>(l.x / r, l.y / r, l.z / r);
    }

    Vector3<T> operator+=(const Vector3<T>& r)
    {
        Vector3& l = *this;
        return l = l + r;
    }

    Vector3<T> operator-=(const Vector3<T>& r)
    {
        Vector3& l = *this;
        return l = l - r;
    }

    Vector3<T> operator*=(float r)
    {
        Vector3& l = *this;
        return l = l * r;
    }

    Vector3<T> operator/=(float r)
    {
        Vector3& l = *this;
        return l = l / r;
    }

    bool operator==(const Vector3<T>& r) const
    {
        const Vector3& l = *this;
        return (l.x == r.x && l.y == r.y && l.z == r.z);
    }

    bool operator!=(const Vector3<T>& r) const
    {
        const Vector3& l = *this;
        return !(l == r);
    }

    T x, y, z;
};

typedef Vector3<float> Vector3f;
typedef Vector3<int> Vector3i;
typedef Vector3<unsigned> Vector3u;

}

#endif // VECTOR3_H
