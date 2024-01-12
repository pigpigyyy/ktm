#ifndef _KTM_I_QUAT_DATA_H_
#define _KTM_I_QUAT_DATA_H_

#include "../../setup.h"
#include "../../type/vec_fwd.h"
#include "../../type/quat_fwd.h"
#include "../../type/mat_fwd.h"
#include "../../function/arithmetic.h"
#include "../../function/geometric.h"

namespace ktm
{
template<class Father, class Child>
struct iquat_data;

template<class Father, typename T>
struct iquat_data<Father, quat<T>> : Father
{
    using Father::Father;
    union
    {
        struct { vec<4, T> vector; };
        struct { T i, j, k, r; };
    };
    constexpr iquat_data(T x, T y, T z, T w) noexcept : i(x), j(y), k(z), r(w) { }
    iquat_data(const vec<4, T>& vec) noexcept : vector(vec) { }

    KTM_INLINE T real() const noexcept { return r; }
    KTM_INLINE vec<3, T> imag() const noexcept { return vec<3, T>(i, j, k); } 
    KTM_INLINE T angle() const noexcept { return static_cast<T>(2) * atan2(length(imag()), real()); }
    KTM_INLINE vec<3, T> axis() const noexcept { return normalize(imag()); }
    KTM_INLINE mat<3, 3, T> matrix3x3() const noexcept 
    {
        mat<3, 3, T> ret;
        matrix(ret);
        return ret;
    }
    KTM_INLINE mat<4, 4, T> matrix4x4() const noexcept 
    {
        mat<4, 4, T> ret = { };
        ret[3][3] = one<T>;
        mat<3, 3, T>* m33_ptr = reinterpret_cast<mat<3, 3, T>*>(&ret);
        matrix(*m33_ptr);
        return ret;
    }
private:
    KTM_NOINLINE void matrix(mat<3, 3, T>& m) const noexcept
    {
        T xx2 = i * i * static_cast<T>(2), yy2 = j * j * static_cast<T>(2), zz2 = k * k * static_cast<T>(2);
        T xy2 = i * j * static_cast<T>(2), xz2 = i * k * static_cast<T>(2), xw2 = i * r * static_cast<T>(2);
        T yz2 = j * k * static_cast<T>(2), yw2 = j * r * static_cast<T>(2), zw2 = k * r * static_cast<T>(2);
        m[0][0] = one<T> - (yy2 + zz2);
        m[0][1] = xy2 + zw2;
        m[0][2] = xz2 - yw2;
        m[1][0] = xy2 - zw2;
        m[1][1] = one<T> - (xx2 + zz2);
        m[1][2] = yz2 + xw2;
        m[2][0] = xz2 + yw2; 
        m[2][1] = yz2 - xw2;
        m[2][2] = one<T> - (yy2 + xx2);
    }
};
}

#endif