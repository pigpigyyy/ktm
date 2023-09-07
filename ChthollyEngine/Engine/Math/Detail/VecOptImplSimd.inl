#ifndef _VEC_OPT_IMPL_SIMD_INL_
#define _VEC_OPT_IMPL_SIMD_INL_

#include "VecOptImpl.h"
#include <Math/MathType/BaseType.h>

#ifdef __ARM_NEON__
#include <arm_neon.h>

template<size_t N>
struct ktm::detail::vec_opt_implement::add<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vadd_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vld1_f32(reinterpret_cast<const float*>(&y)));
            return *(reinterpret_cast<V*>(&ret)); 
        }
        else
        {
            float32x4_t ret = vaddq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vld1q_f32(reinterpret_cast<const float*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vadd_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vld1_f32(reinterpret_cast<const float*>(&y)));
            vst1_f32(reinterpret_cast<float*>(&x), ret);
        }
        else
        {
            float32x4_t ret = vaddq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vld1q_f32(reinterpret_cast<const float*>(&y)));
            vst1q_f32(reinterpret_cast<float*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vsub_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vld1_f32(reinterpret_cast<const float*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            float32x4_t ret = vsubq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vld1q_f32(reinterpret_cast<const float*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vsub_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vld1_f32(reinterpret_cast<const float*>(&y)));
            vst1_f32(reinterpret_cast<float*>(&x), ret);
        }
        else
        {
            float32x4_t ret = vsubq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vld1q_f32(reinterpret_cast<const float*>(&y)));
            vst1q_f32(reinterpret_cast<float*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vmul_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vld1_f32(reinterpret_cast<const float*>(&y)));
            return *(reinterpret_cast<V*>(&ret)); 
        }
        else
        {
            float32x4_t ret = vmulq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vld1q_f32(reinterpret_cast<const float*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vmul_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vld1_f32(reinterpret_cast<const float*>(&y)));
            vst1_f32(reinterpret_cast<float*>(&x), ret);
        }
        else
        {
            float32x4_t ret = vmulq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vld1q_f32(reinterpret_cast<const float*>(&y)));
            vst1q_f32(reinterpret_cast<float*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::div<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vdiv_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vld1_f32(reinterpret_cast<const float*>(&y)));
            return *(reinterpret_cast<V*>(&ret)); 
        }
        else
        {
            float32x4_t ret = vdivq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vld1q_f32(reinterpret_cast<const float*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::div_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vdiv_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vld1_f32(reinterpret_cast<const float*>(&y)));
            vst1_f32(reinterpret_cast<float*>(&x), ret);
        }
        else
        {
            float32x4_t ret = vdivq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vld1q_f32(reinterpret_cast<const float*>(&y)));
            vst1q_f32(reinterpret_cast<float*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::opposite<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vneg_f32(vld1_f32(reinterpret_cast<const float*>(&x)));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            float32x4_t ret = vnegq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_scalar<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vadd_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vdup_n_f32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            float32x4_t ret = vaddq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vdupq_n_f32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
    }

};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_scalar_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V& call(V& x, float scalar) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vadd_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vdup_n_f32(scalar));
            vst1_f32(reinterpret_cast<float*>(&x), ret);
        }
        else
        {
            float32x4_t ret = vaddq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vdupq_n_f32(scalar));
            vst1q_f32(reinterpret_cast<float*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_scalar<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vsub_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vdup_n_f32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            float32x4_t ret = vsubq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vdupq_n_f32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_scalar_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V& call(V& x, float scalar) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vsub_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vdup_n_f32(scalar));
            vst1_f32(reinterpret_cast<float*>(&x), ret);
        }
        else
        {
            float32x4_t ret = vsubq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vdupq_n_f32(scalar));
            vst1q_f32(reinterpret_cast<float*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_scalar<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vmul_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vdup_n_f32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            float32x4_t ret = vmulq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vdupq_n_f32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_scalar_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V& call(V& x, float scalar) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vmul_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vdup_n_f32(scalar));
            vst1_f32(reinterpret_cast<float*>(&x), ret);
        }
        else
        {
            float32x4_t ret = vmulq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vdupq_n_f32(scalar));
            vst1q_f32(reinterpret_cast<float*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::div_scalar<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, float scalar) noexcept
    {   
        if constexpr(N == 2)
        {
            float32x2_t ret = vdiv_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vdup_n_f32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            float32x4_t ret = vdivq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vdupq_n_f32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::div_scalar_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), float>>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V& call(V& x, float scalar) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vdiv_f32(vld1_f32(reinterpret_cast<const float*>(&x)), vdup_n_f32(scalar));
            vst1_f32(reinterpret_cast<float*>(&x), ret);
        }
        else
        {
            float32x4_t ret = vdivq_f32(vld1q_f32(reinterpret_cast<const float*>(&x)), vdupq_n_f32(scalar));
            vst1q_f32(reinterpret_cast<float*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), int>>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vadd_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vld1_s32(reinterpret_cast<const int*>(&y)));
            return *(reinterpret_cast<V*>(&ret)); 
        }
        else
        {
            int32x4_t ret = vaddq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vld1q_s32(reinterpret_cast<const int*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), int>>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vadd_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vld1_s32(reinterpret_cast<const int*>(&y)));
            vst1_s32(reinterpret_cast<int*>(&x), ret);
        }
        else
        {
            int32x4_t ret = vaddq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vld1q_s32(reinterpret_cast<const int*>(&y)));
            vst1q_s32(reinterpret_cast<int*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), int>>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vsub_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vld1_s32(reinterpret_cast<const int*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            int32x4_t ret = vsubq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vld1q_s32(reinterpret_cast<const int*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), int>>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vsub_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vld1_s32(reinterpret_cast<const int*>(&y)));
            vst1_s32(reinterpret_cast<int*>(&x), ret);
        }
        else
        {
            int32x4_t ret = vsubq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vld1q_s32(reinterpret_cast<const int*>(&y)));
            vst1q_s32(reinterpret_cast<int*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), int>>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vmul_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vld1_s32(reinterpret_cast<const int*>(&y)));
            return *(reinterpret_cast<V*>(&ret)); 
        }
        else
        {
            int32x4_t ret = vmulq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vld1q_s32(reinterpret_cast<const int*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), int>>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vmul_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vld1_s32(reinterpret_cast<const int*>(&y)));
            vst1_s32(reinterpret_cast<int*>(&x), ret);
        }
        else
        {
            int32x4_t ret = vmulq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vld1q_s32(reinterpret_cast<const int*>(&y)));
            vst1q_s32(reinterpret_cast<int*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::opposite<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), int>>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vneg_s32(vld1_s32(reinterpret_cast<const int*>(&x)));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            int32x4_t ret = vnegq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_scalar<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), int>>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, int scalar) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vadd_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vdup_n_s32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            int32x4_t ret = vaddq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vdupq_n_s32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
    }

};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_scalar_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), int>>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V& call(V& x, int scalar) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vadd_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vdup_n_s32(scalar));
            vst1_s32(reinterpret_cast<int*>(&x), ret);
        }
        else
        {
            int32x4_t ret = vaddq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vdupq_n_s32(scalar));
            vst1q_s32(reinterpret_cast<int*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_scalar<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), int>>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, int scalar) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vsub_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vdup_n_s32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            int32x4_t ret = vsubq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vdupq_n_s32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_scalar_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), int>>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V& call(V& x, int scalar) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vsub_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vdup_n_s32(scalar));
            vst1_s32(reinterpret_cast<int*>(&x), ret);
        }
        else
        {
            int32x4_t ret = vsubq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vdupq_n_s32(scalar));
            vst1q_s32(reinterpret_cast<int*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_scalar<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), int>>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, int scalar) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vmul_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vdup_n_s32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            int32x4_t ret = vmulq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vdupq_n_s32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_scalar_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), int>>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V& call(V& x, int scalar) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vmul_s32(vld1_s32(reinterpret_cast<const int*>(&x)), vdup_n_s32(scalar));
            vst1_s32(reinterpret_cast<int*>(&x), ret);
        }
        else
        {
            int32x4_t ret = vmulq_s32(vld1q_s32(reinterpret_cast<const int*>(&x)), vdupq_n_s32(scalar));
            vst1q_s32(reinterpret_cast<int*>(&x), ret);
        }
        return x;
    }
};


template<size_t N>
struct ktm::detail::vec_opt_implement::add<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), unsigned int>>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vadd_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vld1_u32(reinterpret_cast<const unsigned int*>(&y)));
            return *(reinterpret_cast<V*>(&ret)); 
        }
        else
        {
            uint32x4_t ret = vaddq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vld1q_u32(reinterpret_cast<const unsigned int*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), unsigned int>>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vadd_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vld1_u32(reinterpret_cast<const unsigned int*>(&y)));
            vst1_u32(reinterpret_cast<unsigned int*>(&x), ret);
        }
        else
        {
            uint32x4_t ret = vaddq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vld1q_u32(reinterpret_cast<const unsigned int*>(&y)));
            vst1q_u32(reinterpret_cast<unsigned int*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), unsigned int>>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vsub_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vld1_u32(reinterpret_cast<const unsigned int*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            uint32x4_t ret = vsubq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vld1q_u32(reinterpret_cast<const unsigned int*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), unsigned int>>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vsub_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vld1_u32(reinterpret_cast<const unsigned int*>(&y)));
            vst1_u32(reinterpret_cast<unsigned int*>(&x), ret);
        }
        else
        {
            uint32x4_t ret = vsubq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vld1q_u32(reinterpret_cast<const unsigned int*>(&y)));
            vst1q_u32(reinterpret_cast<unsigned int*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), unsigned int>>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vmul_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vld1_u32(reinterpret_cast<const unsigned int*>(&y)));
            return *(reinterpret_cast<V*>(&ret)); 
        }
        else
        {
            uint32x4_t ret = vmulq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vld1q_u32(reinterpret_cast<const unsigned int*>(&y)));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), unsigned int>>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vmul_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vld1_u32(reinterpret_cast<const unsigned int*>(&y)));
            vst1_u32(reinterpret_cast<unsigned int*>(&x), ret);
        }
        else
        {
            uint32x4_t ret = vmulq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vld1q_u32(reinterpret_cast<const unsigned int*>(&y)));
            vst1q_u32(reinterpret_cast<unsigned int*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_scalar<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), unsigned int>>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V call(const V& x, unsigned int scalar) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vadd_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vdup_n_u32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            uint32x4_t ret = vaddq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vdupq_n_u32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
    }

};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_scalar_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), unsigned int>>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V& call(V& x, unsigned int scalar) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vadd_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vdup_n_u32(scalar));
            vst1_u32(reinterpret_cast<unsigned int*>(&x), ret);
        }
        else
        {
            uint32x4_t ret = vaddq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vdupq_n_u32(scalar));
            vst1q_u32(reinterpret_cast<unsigned int*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_scalar<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), unsigned int>>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V call(const V& x, unsigned int scalar) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vsub_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vdup_n_u32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            uint32x4_t ret = vsubq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vdupq_n_u32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_scalar_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), unsigned int>>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V& call(V& x, unsigned int scalar) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vsub_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vdup_n_u32(scalar));
            vst1_u32(reinterpret_cast<unsigned int*>(&x), ret);
        }
        else
        {
            uint32x4_t ret = vsubq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vdupq_n_u32(scalar));
            vst1q_u32(reinterpret_cast<unsigned int*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_scalar<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), unsigned int>>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V call(const V& x, unsigned int scalar) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vmul_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vdup_n_u32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
        else
        {
            uint32x4_t ret = vmulq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vdupq_n_u32(scalar));
            return *(reinterpret_cast<V*>(&ret));
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_scalar_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), unsigned int>>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V& call(V& x, unsigned int scalar) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vmul_u32(vld1_u32(reinterpret_cast<const unsigned int*>(&x)), vdup_n_u32(scalar));
            vst1_u32(reinterpret_cast<unsigned int*>(&x), ret);
        }
        else
        {
            uint32x4_t ret = vmulq_u32(vld1q_u32(reinterpret_cast<const unsigned int*>(&x)), vdupq_n_u32(scalar));
            vst1q_u32(reinterpret_cast<unsigned int*>(&x), ret);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), double>>>
{
    using V = vec<N, double>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float64x2_t ret = vaddq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vld1q_f64(reinterpret_cast<const double*>(&y)));
            return *(reinterpret_cast<V*>(&ret)); 
        }
        else if constexpr(N == 3)
        {
            V ret;
            float64x2_t lo = vaddq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vld1q_f64(reinterpret_cast<const double*>(&y)));
            float64x1_t hi = vadd_f64(vld1_f64(reinterpret_cast<const double*>(&x) + 2), vld1_f64(reinterpret_cast<const double*>(&y) + 2));
            vst1q_f64(reinterpret_cast<double*>(&ret), lo);
            vst1_f64(reinterpret_cast<double*>(&ret) + 2, hi);
            return ret;
        }
        else
        {
            V ret;
            float64x2_t lo = vaddq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vld1q_f64(reinterpret_cast<const double*>(&y)));
            float64x2_t hi = vaddq_f64(vld1q_f64(reinterpret_cast<const double*>(&x) + 2), vld1q_f64(reinterpret_cast<const double*>(&y) + 2));
            vst1q_f64(reinterpret_cast<double*>(&ret), lo);
            vst1q_f64(reinterpret_cast<double*>(&ret) + 2, hi);
            return ret;
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), double>>>
{
    using V = vec<N, double>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float64x2_t ret = vaddq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vld1q_f64(reinterpret_cast<const double*>(&y)));
            vst1q_f64(reinterpret_cast<double*>(&x), ret);
        }
        else if constexpr(N == 3)
        {
            float64x2_t lo = vaddq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vld1q_f64(reinterpret_cast<const double*>(&y)));
            float64x1_t hi = vadd_f64(vld1_f64(reinterpret_cast<const double*>(&x) + 2), vld1_f64(reinterpret_cast<const double*>(&y) + 2));
            vst1q_f64(reinterpret_cast<double*>(&x), lo);
            vst1_f64(reinterpret_cast<double*>(&x) + 2, hi);
        }
        else
        {
            float64x2_t lo = vaddq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vld1q_f64(reinterpret_cast<const double*>(&y)));
            float64x2_t hi = vaddq_f64(vld1q_f64(reinterpret_cast<const double*>(&x) + 2), vld1q_f64(reinterpret_cast<const double*>(&y) + 2));
            vst1q_f64(reinterpret_cast<double*>(&x), lo);
            vst1q_f64(reinterpret_cast<double*>(&x) + 2, hi);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), double>>>
{
    using V = vec<N, double>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float64x2_t ret = vsubq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vld1q_f64(reinterpret_cast<const double*>(&y)));
            return *(reinterpret_cast<V*>(&ret)); 
        }
        else if constexpr(N == 3)
        {
            V ret;
            float64x2_t lo = vsubq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vld1q_f64(reinterpret_cast<const double*>(&y)));
            float64x1_t hi = vsub_f64(vld1_f64(reinterpret_cast<const double*>(&x) + 2), vld1_f64(reinterpret_cast<const double*>(&y) + 2));
            vst1q_f64(reinterpret_cast<double*>(&ret), lo);
            vst1_f64(reinterpret_cast<double*>(&ret) + 2, hi);
            return ret;
        }
        else
        {
            V ret;
            float64x2_t lo = vsubq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vld1q_f64(reinterpret_cast<const double*>(&y)));
            float64x2_t hi = vsubq_f64(vld1q_f64(reinterpret_cast<const double*>(&x) + 2), vld1q_f64(reinterpret_cast<const double*>(&y) + 2));
            vst1q_f64(reinterpret_cast<double*>(&ret), lo);
            vst1q_f64(reinterpret_cast<double*>(&ret) + 2, hi);
            return ret;
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), double>>>
{
    using V = vec<N, double>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float64x2_t ret = vsubq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vld1q_f64(reinterpret_cast<const double*>(&y)));
            vst1q_f64(reinterpret_cast<double*>(&x), ret);
        }
        else if constexpr(N == 3)
        {
            float64x2_t lo = vsubq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vld1q_f64(reinterpret_cast<const double*>(&y)));
            float64x1_t hi = vsub_f64(vld1_f64(reinterpret_cast<const double*>(&x) + 2), vld1_f64(reinterpret_cast<const double*>(&y) + 2));
            vst1q_f64(reinterpret_cast<double*>(&x), lo);
            vst1_f64(reinterpret_cast<double*>(&x) + 2, hi);
        }
        else
        {
            float64x2_t lo = vsubq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vld1q_f64(reinterpret_cast<const double*>(&y)));
            float64x2_t hi = vsubq_f64(vld1q_f64(reinterpret_cast<const double*>(&x) + 2), vld1q_f64(reinterpret_cast<const double*>(&y) + 2));
            vst1q_f64(reinterpret_cast<double*>(&x), lo);
            vst1q_f64(reinterpret_cast<double*>(&x) + 2, hi);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), double>>>
{
    using V = vec<N, double>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float64x2_t ret = vmulq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vld1q_f64(reinterpret_cast<const double*>(&y)));
            return *(reinterpret_cast<V*>(&ret)); 
        }
        else if constexpr(N == 3)
        {
            V ret;
            float64x2_t lo = vmulq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vld1q_f64(reinterpret_cast<const double*>(&y)));
            float64x1_t hi = vmul_f64(vld1_f64(reinterpret_cast<const double*>(&x) + 2), vld1_f64(reinterpret_cast<const double*>(&y) + 2));
            vst1q_f64(reinterpret_cast<double*>(&ret), lo);
            vst1_f64(reinterpret_cast<double*>(&ret) + 2, hi);
            return ret;
        }
        else
        {
            V ret;
            float64x2_t lo = vmulq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vld1q_f64(reinterpret_cast<const double*>(&y)));
            float64x2_t hi = vmulq_f64(vld1q_f64(reinterpret_cast<const double*>(&x) + 2), vld1q_f64(reinterpret_cast<const double*>(&y) + 2));
            vst1q_f64(reinterpret_cast<double*>(&ret), lo);
            vst1q_f64(reinterpret_cast<double*>(&ret) + 2, hi);
            return ret;
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), double>>>
{
    using V = vec<N, double>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float64x2_t ret = vmulq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vld1q_f64(reinterpret_cast<const double*>(&y)));
            vst1q_f64(reinterpret_cast<double*>(&x), ret);
        }
        else if constexpr(N == 3)
        {
            float64x2_t lo = vmulq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vld1q_f64(reinterpret_cast<const double*>(&y)));
            float64x1_t hi = vmul_f64(vld1_f64(reinterpret_cast<const double*>(&x) + 2), vld1_f64(reinterpret_cast<const double*>(&y) + 2));
            vst1q_f64(reinterpret_cast<double*>(&x), lo);
            vst1_f64(reinterpret_cast<double*>(&x) + 2, hi);
        }
        else
        {
            float64x2_t lo = vmulq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vld1q_f64(reinterpret_cast<const double*>(&y)));
            float64x2_t hi = vmulq_f64(vld1q_f64(reinterpret_cast<const double*>(&x) + 2), vld1q_f64(reinterpret_cast<const double*>(&y) + 2));
            vst1q_f64(reinterpret_cast<double*>(&x), lo);
            vst1q_f64(reinterpret_cast<double*>(&x) + 2, hi);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::div<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), double>>>
{
    using V = vec<N, double>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float64x2_t ret = vdivq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vld1q_f64(reinterpret_cast<const double*>(&y)));
            return *(reinterpret_cast<V*>(&ret)); 
        }
        else if constexpr(N == 3)
        {
            V ret;
            float64x2_t lo = vdivq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vld1q_f64(reinterpret_cast<const double*>(&y)));
            float64x1_t hi = vdiv_f64(vld1_f64(reinterpret_cast<const double*>(&x) + 2), vld1_f64(reinterpret_cast<const double*>(&y) + 2));
            vst1q_f64(reinterpret_cast<double*>(&ret), lo);
            vst1_f64(reinterpret_cast<double*>(&ret) + 2, hi);
            return ret;
        }
        else
        {
            V ret;
            float64x2_t lo = vdivq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vld1q_f64(reinterpret_cast<const double*>(&y)));
            float64x2_t hi = vdivq_f64(vld1q_f64(reinterpret_cast<const double*>(&x) + 2), vld1q_f64(reinterpret_cast<const double*>(&y) + 2));
            vst1q_f64(reinterpret_cast<double*>(&ret), lo);
            vst1q_f64(reinterpret_cast<double*>(&ret) + 2, hi);
            return ret;
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::div_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), double>>>
{
    using V = vec<N, double>;
    static CHTHOLLY_INLINE V& call(V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float64x2_t ret = vdivq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vld1q_f64(reinterpret_cast<const double*>(&y)));
            vst1q_f64(reinterpret_cast<double*>(&x), ret);
        }
        else if constexpr(N == 3)
        {
            float64x2_t lo = vdivq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vld1q_f64(reinterpret_cast<const double*>(&y)));
            float64x1_t hi = vdiv_f64(vld1_f64(reinterpret_cast<const double*>(&x) + 2), vld1_f64(reinterpret_cast<const double*>(&y) + 2));
            vst1q_f64(reinterpret_cast<double*>(&x), lo);
            vst1_f64(reinterpret_cast<double*>(&x) + 2, hi);
        }
        else
        {
            float64x2_t lo = vdivq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vld1q_f64(reinterpret_cast<const double*>(&y)));
            float64x2_t hi = vdivq_f64(vld1q_f64(reinterpret_cast<const double*>(&x) + 2), vld1q_f64(reinterpret_cast<const double*>(&y) + 2));
            vst1q_f64(reinterpret_cast<double*>(&x), lo);
            vst1q_f64(reinterpret_cast<double*>(&x) + 2, hi);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::opposite<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), double>>>
{
    using V = vec<N, double>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            float64x2_t ret = vnegq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)));
            return *(reinterpret_cast<V*>(&ret)); 
        }
        else if constexpr(N == 3)
        {
            V ret;
            float64x2_t lo = vnegq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)));
            float64x1_t hi = vneg_f64(vld1_f64(reinterpret_cast<const double*>(&x) + 2));
            vst1q_f64(reinterpret_cast<double*>(&ret), lo);
            vst1_f64(reinterpret_cast<double*>(&ret) + 2, hi);
            return ret;
        }
        else
        {
            V ret;
            float64x2_t lo = vnegq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)));
            float64x2_t hi = vnegq_f64(vld1q_f64(reinterpret_cast<const double*>(&x) + 2));
            vst1q_f64(reinterpret_cast<double*>(&ret), lo);
            vst1q_f64(reinterpret_cast<double*>(&ret) + 2, hi);
            return ret;
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_scalar<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), double>>>
{
    using V = vec<N, double>;
    static CHTHOLLY_INLINE V call(const V& x, double scalar) noexcept
    {
        if constexpr(N == 2)
        {
            float64x2_t ret = vaddq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vdupq_n_f64(scalar));
            return *(reinterpret_cast<V*>(&ret)); 
        }
        else if constexpr(N == 3)
        {
            V ret;
            float64x2_t lo = vaddq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vdupq_n_f64(scalar));
            float64x1_t hi = vadd_f64(vld1_f64(reinterpret_cast<const double*>(&x) + 2), vdup_n_f64(scalar));
            vst1q_f64(reinterpret_cast<double*>(&ret), lo);
            vst1_f64(reinterpret_cast<double*>(&ret) + 2, hi);
            return ret;
        }
        else
        {
            V ret;
            float64x2_t lo = vaddq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vdupq_n_f64(scalar));
            float64x2_t hi = vaddq_f64(vld1q_f64(reinterpret_cast<const double*>(&x) + 2), vdupq_n_f64(scalar));
            vst1q_f64(reinterpret_cast<double*>(&ret), lo);
            vst1q_f64(reinterpret_cast<double*>(&ret) + 2, hi);
            return ret;
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::add_scalar_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), double>>>
{
    using V = vec<N, double>;
    static CHTHOLLY_INLINE V& call(V& x, double scalar) noexcept
    {
        if constexpr(N == 2)
        {
            float64x2_t ret = vaddq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vdupq_n_f64(scalar));
            vst1q_f64(reinterpret_cast<double*>(&x), ret);
        }
        else if constexpr(N == 3)
        {
            float64x2_t lo = vaddq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vdupq_n_f64(scalar));
            float64x1_t hi = vadd_f64(vld1_f64(reinterpret_cast<const double*>(&x) + 2), vdup_n_f64(scalar));
            vst1q_f64(reinterpret_cast<double*>(&x), lo);
            vst1_f64(reinterpret_cast<double*>(&x) + 2, hi);
        }
        else
        {
            float64x2_t lo = vaddq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vdupq_n_f64(scalar));
            float64x2_t hi = vaddq_f64(vld1q_f64(reinterpret_cast<const double*>(&x) + 2), vdupq_n_f64(scalar));
            vst1q_f64(reinterpret_cast<double*>(&x), lo);
            vst1q_f64(reinterpret_cast<double*>(&x) + 2, hi);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_scalar<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), double>>>
{
    using V = vec<N, double>;
    static CHTHOLLY_INLINE V call(const V& x, double scalar) noexcept
    {
        if constexpr(N == 2)
        {
            float64x2_t ret = vsubq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vdupq_n_f64(scalar));
            return *(reinterpret_cast<V*>(&ret)); 
        }
        else if constexpr(N == 3)
        {
            V ret;
            float64x2_t lo = vsubq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vdupq_n_f64(scalar));
            float64x1_t hi = vsub_f64(vld1_f64(reinterpret_cast<const double*>(&x) + 2), vdup_n_f64(scalar));
            vst1q_f64(reinterpret_cast<double*>(&ret), lo);
            vst1_f64(reinterpret_cast<double*>(&ret) + 2, hi);
            return ret;
        }
        else
        {
            V ret;
            float64x2_t lo = vsubq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vdupq_n_f64(scalar));
            float64x2_t hi = vsubq_f64(vld1q_f64(reinterpret_cast<const double*>(&x) + 2), vdupq_n_f64(scalar));
            vst1q_f64(reinterpret_cast<double*>(&ret), lo);
            vst1q_f64(reinterpret_cast<double*>(&ret) + 2, hi);
            return ret;
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::minus_scalar_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), double>>>
{
    using V = vec<N, double>;
    static CHTHOLLY_INLINE V& call(V& x, double scalar) noexcept
    {
        if constexpr(N == 2)
        {
            float64x2_t ret = vsubq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vdupq_n_f64(scalar));
            vst1q_f64(reinterpret_cast<double*>(&x), ret);
        }
        else if constexpr(N == 3)
        {
            float64x2_t lo = vsubq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vdupq_n_f64(scalar));
            float64x1_t hi = vsub_f64(vld1_f64(reinterpret_cast<const double*>(&x) + 2), vdup_n_f64(scalar));
            vst1q_f64(reinterpret_cast<double*>(&x), lo);
            vst1_f64(reinterpret_cast<double*>(&x) + 2, hi);
        }
        else
        {
            float64x2_t lo = vsubq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vdupq_n_f64(scalar));
            float64x2_t hi = vsubq_f64(vld1q_f64(reinterpret_cast<const double*>(&x) + 2), vdupq_n_f64(scalar));
            vst1q_f64(reinterpret_cast<double*>(&x), lo);
            vst1q_f64(reinterpret_cast<double*>(&x) + 2, hi);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_scalar<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), double>>>
{
    using V = vec<N, double>;
    static CHTHOLLY_INLINE V call(const V& x, double scalar) noexcept
    {
        if constexpr(N == 2)
        {
            float64x2_t ret = vmulq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vdupq_n_f64(scalar));
            return *(reinterpret_cast<V*>(&ret)); 
        }
        else if constexpr(N == 3)
        {
            V ret;
            float64x2_t lo = vmulq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vdupq_n_f64(scalar));
            float64x1_t hi = vmul_f64(vld1_f64(reinterpret_cast<const double*>(&x) + 2), vdup_n_f64(scalar));
            vst1q_f64(reinterpret_cast<double*>(&ret), lo);
            vst1_f64(reinterpret_cast<double*>(&ret) + 2, hi);
            return ret;
        }
        else
        {
            V ret;
            float64x2_t lo = vmulq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vdupq_n_f64(scalar));
            float64x2_t hi = vmulq_f64(vld1q_f64(reinterpret_cast<const double*>(&x) + 2), vdupq_n_f64(scalar));
            vst1q_f64(reinterpret_cast<double*>(&ret), lo);
            vst1q_f64(reinterpret_cast<double*>(&ret) + 2, hi);
            return ret;
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::mul_scalar_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), double>>>
{
    using V = vec<N, double>;
    static CHTHOLLY_INLINE V& call(V& x, double scalar) noexcept
    {
        if constexpr(N == 2)
        {
            float64x2_t ret = vmulq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vdupq_n_f64(scalar));
            vst1q_f64(reinterpret_cast<double*>(&x), ret);
        }
        else if constexpr(N == 3)
        {
            float64x2_t lo = vmulq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vdupq_n_f64(scalar));
            float64x1_t hi = vmul_f64(vld1_f64(reinterpret_cast<const double*>(&x) + 2), vdup_n_f64(scalar));
            vst1q_f64(reinterpret_cast<double*>(&x), lo);
            vst1_f64(reinterpret_cast<double*>(&x) + 2, hi);
        }
        else
        {
            float64x2_t lo = vmulq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vdupq_n_f64(scalar));
            float64x2_t hi = vmulq_f64(vld1q_f64(reinterpret_cast<const double*>(&x) + 2), vdupq_n_f64(scalar));
            vst1q_f64(reinterpret_cast<double*>(&x), lo);
            vst1q_f64(reinterpret_cast<double*>(&x) + 2, hi);
        }
        return x;
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::div_scalar<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), double>>>
{
    using V = vec<N, double>;
    static CHTHOLLY_INLINE V call(const V& x, double scalar) noexcept
    {   
        if constexpr(N == 2)
        {
            float64x2_t ret = vdivq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vdupq_n_f64(scalar));
            return *(reinterpret_cast<V*>(&ret)); 
        }
        else if constexpr(N == 3)
        {
            V ret;
            float64x2_t lo = vdivq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vdupq_n_f64(scalar));
            float64x1_t hi = vdiv_f64(vld1_f64(reinterpret_cast<const double*>(&x) + 2), vdup_n_f64(scalar));
            vst1q_f64(reinterpret_cast<double*>(&ret), lo);
            vst1_f64(reinterpret_cast<double*>(&ret) + 2, hi);
            return ret;
        }
        else
        {
            V ret;
            float64x2_t lo = vdivq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vdupq_n_f64(scalar));
            float64x2_t hi = vdivq_f64(vld1q_f64(reinterpret_cast<const double*>(&x) + 2), vdupq_n_f64(scalar));
            vst1q_f64(reinterpret_cast<double*>(&ret), lo);
            vst1q_f64(reinterpret_cast<double*>(&ret) + 2, hi);
            return ret;
        }
    }
};

template<size_t N>
struct ktm::detail::vec_opt_implement::div_scalar_to_self<ktm::vec<N, std::enable_if_t<(N >= 2 && N <= 4), double>>>
{
    using V = vec<N, double>;
    static CHTHOLLY_INLINE V& call(V& x, float scalar) noexcept
    {
        if constexpr(N == 2)
        {
            float64x2_t ret = vdivq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vdupq_n_f64(scalar));
            vst1q_f64(reinterpret_cast<double*>(&x), ret);
        }
        else if constexpr(N == 3)
        {
            float64x2_t lo = vdivq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vdupq_n_f64(scalar));
            float64x1_t hi = vdiv_f64(vld1_f64(reinterpret_cast<const double*>(&x) + 2), vdup_n_f64(scalar));
            vst1q_f64(reinterpret_cast<double*>(&x), lo);
            vst1_f64(reinterpret_cast<double*>(&x) + 2, hi);
        }
        else
        {
            float64x2_t lo = vdivq_f64(vld1q_f64(reinterpret_cast<const double*>(&x)), vdupq_n_f64(scalar));
            float64x2_t hi = vdivq_f64(vld1q_f64(reinterpret_cast<const double*>(&x) + 2), vdupq_n_f64(scalar));
            vst1q_f64(reinterpret_cast<double*>(&x), lo);
            vst1q_f64(reinterpret_cast<double*>(&x) + 2, hi);
        }
        return x;
    }
};

#endif

#endif