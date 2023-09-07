#ifndef _VEC_GEOMETRY_H_
#define _VEC_GEOMETRY_H_

#include "Math/MathType/VecType.h"
#include "Math/MathLib/VecCommon.h"

namespace ktm
{
    template<class V>
    static CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<vec_traits_t<V>>, vec_traits_t<V>> dot(const V& x, const V& y)
    {
        return reduce_add(x * y); 
    }

    template<class V>
    static CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<vec_traits_t<V>>, V> project(const V& x, const V& y)
    {
        return dot(x, y) / dot(y, y) * y; 
    }

    template<class V>
    static CHTHOLLY_INLINE std::enable_if_t<(std::is_floating_point_v<vec_traits_t<V>> && vec_traits_len<V> == 3), V> cross(const V& x, const V& y)
    {
        return { x[1] * y[2] - x[2] * y[1], x[2] * y[0] - x[0] * y[2], x[0] * y[1] - x[1] * y[0] };
    }

    template<class V>
    static CHTHOLLY_INLINE std::enable_if_t<(std::is_floating_point_v<vec_traits_t<V>> && vec_traits_len<V> == 2), vec<3, vec_traits_t<V>>> cross(const V& x, const V& y)
    {
        return { zero<vec_traits_t<V>>, zero<vec_traits_t<V>>, x[0] * y[1] - x[1] * y[0] };
    }

    template<class V>
    static CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<vec_traits_t<V>>, vec_traits_t<V>> length_squared(const V& x)
    {
        return dot(x, x);
    }

    template<class V>
    static CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<vec_traits_t<V>>, vec_traits_t<V>> length(const V& x)
    {
        return sqrt(length_squared(x));
    }

    template<class V>
    static CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<vec_traits_t<V>>, vec_traits_t<V>> distance(const V& x, const V& y)
    {
        return length(y - x);
    }

    template<class V>
    static CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<vec_traits_t<V>>, V> nomorlize(const V& x)
    {
        return rsqrt(length_squared(x)) * x;
    }

    template<class V>
    static CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<vec_traits_t<V>>, V> reflect(const V& x, const V& n)
    {
        return x - 2 * dot(x, n) * n;
    }

    template<class V>
    static CHTHOLLY_INLINE std::enable_if_t<std::is_floating_point_v<vec_traits_t<V>>, V> refract(const V& x, const V& n, vec_traits_t<V> eta)
    {
        using value_type = vec_traits_t<V>;
        const value_type k = one<value_type> - eta * eta * (one<value_type> - dot(x, n) * dot(x, n));
        return k >= zero<value_type> ? eta * x - (eta * dot(x, n) + sqrt(k)) * n : V();
    }
}

#endif