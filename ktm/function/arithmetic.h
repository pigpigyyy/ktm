//  MIT License
//
//  Copyright (c) 2023 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_ARITHMETIC_H_
#define _KTM_ARITHMETIC_H_

#include <cmath>
#include "../setup.h"
#include "../type/basic.h"

namespace ktm
{

template<typename T>
KTM_INLINE std::enable_if_t<(std::is_arithmetic_v<T> && !std::is_unsigned_v<T>), T> abs(T x) noexcept
{
    if constexpr(std::is_same_v<float, T>)
    {
        unsigned int ret = *reinterpret_cast<unsigned int*>(&x) & 0x7fffffff;
        return *reinterpret_cast<float*>(&ret);
    }
    else if constexpr(std::is_same_v<double, T>)
    {
        unsigned long long ret = *reinterpret_cast<unsigned long long*>(&x) & 0x7fffffffffffffff;
        return *reinterpret_cast<double*>(&ret);
    }
    else
        return x < 0 ? -x : x;
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_arithmetic_v<T>, T> min(T x, T y) noexcept
{
    return x < y ? x : y;
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_arithmetic_v<T>, T> max(T x, T y) noexcept
{
    return x > y ? x : y;
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_arithmetic_v<T>, T> clamp(T v, T min_v, T max_v) noexcept
{
    return min(max(v, min_v), max_v);
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> floor(T x) noexcept
{
    if constexpr(std::is_same_v<T, float>)
        return ::floorf(x);
    else if constexpr(std::is_same_v<T, double>)
        return ::floor(x);
    else 
        return ::floorl(x);
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> ceil(T x) noexcept
{
    if constexpr(std::is_same_v<T, float>)
        return ::ceilf(x);
    else if constexpr(std::is_same_v<T, double>)
        return ::ceil(x);
    else 
        return ::ceill(x);
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> round(T x) noexcept
{
    if constexpr(std::is_same_v<T, float>)
        return ::roundf(x);
    else if constexpr(std::is_same_v<T, double>)
        return ::round(x);
    else 
        return ::roundl(x);
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> fract(T x) noexcept
{
    return x - floor(x);
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> mod(T x, T y) noexcept
{
    return x - y * floor(x / y);
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> lerp(T x, T y, T t) noexcept
{
    return x + t * (y - x);
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> mix(T x, T y, T t) noexcept
{
    return lerp(x, y, t);
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> step(T edge, T x) noexcept
{
    return x < edge ? one<T> : zero<T>;
}

template<typename T>
KTM_INLINE std::enable_if_t<std::is_floating_point_v<T>, T> smoothstep(T edge0, T edge1, T x) noexcept
{
    const T tmp = clamp((x - edge0) / (edge1 - edge0), zero<T>, one<T>);
    return tmp * tmp * (static_cast<T>(3) - static_cast<T>(2) * tmp);
}

}

#endif