//  MIT License
//
//  Copyright (c) 2023 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_COMMON_INL_
#define _KTM_COMMON_INL_

#include "common_fwd.h"
#include "../loop_util.h"
#include "../../type/vec_fwd.h"
#include "../../function/arithmetic.h"
#include "../../function/exponential.h"

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::reduce_add
{
    using V = vec<N, T>;
    static KTM_INLINE T call(const V& x) noexcept
    {
        T ret = x[0];
        loop_op<N - 1, void>::call(
            [&ret](const T& x) -> void { ret += x; }, &x[1]);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::reduce_min
{
    using V = vec<N, T>;
    static KTM_INLINE T call(const V& x) noexcept
    {
        T ret = x[0];
        loop_op<N - 1, void>::call(
            [&ret](const T& x) -> void { ret = ktm::min<T>(ret, x); }, &x[1]);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::reduce_max
{
    using V = vec<N, T>;
    static KTM_INLINE T call(const V& x) noexcept
    {
        T ret = x[0];
        loop_op<N - 1, void>::call(
            [&ret](const T& x) -> void { ret = ktm::max<T>(ret, x); }, &x[1]);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::abs
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N, V>::call(ret, ktm::abs<T>, x);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::min
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        loop_op<N, V>::call(ret, ktm::min<T>, x, y);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::max
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        loop_op<N, V>::call(ret, ktm::max<T>, x, y);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::clamp
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        V ret;
        loop_op<N, V>::call(ret, ktm::clamp<T>, v, min, max);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::floor
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N, V>::call(ret, ktm::floor<T>, x);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::ceil
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N, V>::call(ret, ktm::ceil<T>, x);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::round
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N, V>::call(ret, ktm::round<T>, x);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::fract
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N, V>::call(ret, ktm::fract<T>, x);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::mod
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x, const V& y) noexcept
    {
        V ret;
        loop_op<N, V>::call(ret, ktm::mod<T>, x, y);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::lerp
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x, const V& y, T t) noexcept
    {
        V ret;
        loop_op<N, V>::call(ret, 
            [&t](const T& x, const T& y) -> T { return ktm::lerp<T>(x, y, t); }, x, y);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::mix
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x, const V& y, const V& t) noexcept
    {
        V ret;
        loop_op<N, V>::call(ret, ktm::lerp<T>, x, y, t);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::step
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& edge, const V& x) noexcept
    {
        V ret;
        loop_op<N, V>::call(ret, ktm::step<T>, edge, x);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::smoothstep
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& edge0, const V& edge1, const V& x) noexcept
    {
        V ret;
        loop_op<N, V>::call(ret, ktm::smoothstep<T>, edge0, edge1, x);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::sqrt
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N, V>::call(ret, ktm::sqrt<T>, x);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::rsqrt
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N, V>::call(ret, ktm::rsqrt<T>, x);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::recip
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N, V>::call(ret, ktm::recip<T>, x);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::fast_sqrt
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N, V>::call(ret, ktm::fast::sqrt<T>, x);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::fast_rsqrt
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N, V>::call(ret, ktm::fast::rsqrt<T>, x);
        return ret;
    }
};

template<size_t N, typename T, typename Void>
struct ktm::detail::common_implement::fast_recip
{
    using V = vec<N, T>;
    static KTM_INLINE V call(const V& x) noexcept
    {
        V ret;
        loop_op<N, V>::call(ret, ktm::fast::recip<T>, x);
        return ret;
    }
};

#endif
