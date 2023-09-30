#ifndef _VEC_COMMON_IMPL_SIMD_INL_
#define _VEC_COMMON_IMPL_SIMD_INL_

#include "VecCommonImpl.h"
#include "Math/MathLib/Common.h"

#if defined(CHTHOLLY_SIMD_NEON)
#include <arm_neon.h>

template<size_t L, size_t N>
struct ktm::detail::vec_common_implement::elem_move<L, N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    static_assert(L > 0 && L < N);
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            constexpr size_t i1 = 1 + L < N ? 1 + L : 1 + L - N;
            float32x2_t ret = vld1_f32(&x[0]);
            ret = __builtin_shufflevector(ret, ret, L, i1);
            return *reinterpret_cast<V*>(&ret);
        }
        else if constexpr(N == 3)
        {
            constexpr size_t i1 = 1 + L < N ? 1 + L : 1 + L - N;
            constexpr size_t i2 = 2 + L < N ? 2 + L : 2 + L - N; 
            float32x4_t ret = vld1q_f32(&x[0]);
            ret = __builtin_shufflevector(ret, ret, L, i1, i2, 3);
            return *reinterpret_cast<V*>(&ret);
        }
        else if constexpr(N == 4)
        {
            constexpr size_t i1 = 1 + L < N ? 1 + L : 1 + L - N;
            constexpr size_t i2 = 2 + L < N ? 2 + L : 2 + L - N; 
            constexpr size_t i3 = 3 + L < N ? 3 + L : 3 + L - N;  
            float32x4_t ret = vld1q_f32(&x[0]);
            ret = __builtin_shufflevector(ret, ret, L, i1, i2, i3);
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t L, size_t N>
struct ktm::detail::vec_common_implement::elem_move<L, N, std::enable_if_t<N >= 2 && N <= 4, int>>
{
    static_assert(L > 0 && L < N);
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            constexpr size_t i1 = 1 + L < N ? 1 + L : 1 + L - N;
            int32x2_t ret = vld1_s32(&x[0]);
            ret = __builtin_shufflevector(ret, ret, L, i1);
            return *reinterpret_cast<V*>(&ret);
        }
        else if constexpr(N == 3)
        {
            constexpr size_t i1 = 1 + L < N ? 1 + L : 1 + L - N;
            constexpr size_t i2 = 2 + L < N ? 2 + L : 2 + L - N; 
            int32x4_t ret = vld1q_s32(&x[0]);
            ret = __builtin_shufflevector(ret, ret, L, i1, i2, 3);
            return *reinterpret_cast<V*>(&ret);
        }
        else if constexpr(N == 4)
        {
            constexpr size_t i1 = 1 + L < N ? 1 + L : 1 + L - N;
            constexpr size_t i2 = 2 + L < N ? 2 + L : 2 + L - N; 
            constexpr size_t i3 = 3 + L < N ? 3 + L : 3 + L - N;  
            int32x4_t ret = vld1q_s32(&x[0]);
            ret = __builtin_shufflevector(ret, ret, L, i1, i2, i3);
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t L, size_t N>
struct ktm::detail::vec_common_implement::elem_move<L, N, std::enable_if_t<N >= 2 && N <= 4, unsigned int>>
{
    static_assert(L > 0 && L < N);
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            constexpr size_t i1 = 1 + L < N ? 1 + L : 1 + L - N;
            uint32x2_t ret = vld1_u32(&x[0]);
            ret = __builtin_shufflevector(ret, ret, L, i1);
            return *reinterpret_cast<V*>(&ret);
        }
        else if constexpr(N == 3)
        {
            constexpr size_t i1 = 1 + L < N ? 1 + L : 1 + L - N;
            constexpr size_t i2 = 2 + L < N ? 2 + L : 2 + L - N; 
            uint32x4_t ret = vld1q_u32(&x[0]);
            ret = __builtin_shufflevector(ret, ret, L, i1, i2, 3);
            return *reinterpret_cast<V*>(&ret);
        }
        else if constexpr(N == 4)
        {
            constexpr size_t i1 = 1 + L < N ? 1 + L : 1 + L - N;
            constexpr size_t i2 = 2 + L < N ? 2 + L : 2 + L - N; 
            constexpr size_t i3 = 3 + L < N ? 3 + L : 3 + L - N;  
            uint32x4_t ret = vld1q_u32(&x[0]);
            ret = __builtin_shufflevector(ret, ret, L, i1, i2, i3);
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::reduce_add<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE float call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            return vaddv_f32(vld1_f32(&x[0]));
        }
        else if constexpr(N == 3)
        {
            float32x4_t tmp = vld1q_f32(&x[0]);
            return vaddvq_f32(vsetq_lane_f32(zero<float>, tmp, 3)); 
        }
        else
        {
            return vaddvq_f32(vld1q_f32(&x[0])); 
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::reduce_add<N, std::enable_if_t<N >= 2 && N <= 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE int call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            return vaddv_s32(vld1_s32(&x[0]));
        }
        else if constexpr(N == 3)
        {
            int32x4_t tmp = vld1q_s32(&x[0]);
            return vaddvq_s32(vsetq_lane_s32(zero<int>, tmp, 3)); 
        }
        else
        {
            return vaddvq_s32(vld1q_s32(&x[0])); 
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::reduce_add<N, std::enable_if_t<N >= 2 && N <= 4, unsigned int>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE unsigned int call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            return vaddv_u32(vld1_u32(&x[0]));
        }
        else if constexpr(N == 3)
        {
            uint32x4_t tmp = vld1q_u32(&x[0]);
            return vaddvq_u32(vsetq_lane_u32(zero<unsigned int>, tmp, 3)); 
        }
        else
        {
            return vaddvq_u32(vld1q_u32(&x[0])); 
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::reduce_min<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE float call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            return vminv_f32(vld1_f32(&x[0]));
        }
        else if constexpr(N == 3)
        {
            float32x4_t tmp = vld1q_f32(&x[0]);
            return vminvq_f32(vsetq_lane_f32(tmp[2], tmp, 3)); 
        }
        else
        {
            return vminvq_f32(vld1q_f32(&x[0])); 
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::reduce_min<N, std::enable_if_t<N >= 2 && N <= 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE int call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            return vminv_s32(vld1_s32(&x[0]));
        }
        else if constexpr(N == 3)
        {
            int32x4_t tmp = vld1q_s32(&x[0]);
            return vminvq_s32(vsetq_lane_s32(tmp[2], tmp, 3)); 
        }
        else
        {
            return vminvq_s32(vld1q_s32(&x[0])); 
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::reduce_min<N, std::enable_if_t<N >= 2 && N <= 4, unsigned int>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE unsigned int call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            return vminv_u32(vld1_u32(&x[0]));
        }
        else if constexpr(N == 3)
        {
            uint32x4_t tmp = vld1q_u32(&x[0]);
            return vminvq_u32(vsetq_lane_u32(tmp[2], tmp, 3)); 
        }
        else
        {
            return vminvq_u32(vld1q_u32(&x[0])); 
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::reduce_max<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE float call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            return vmaxv_f32(vld1_f32(&x[0]));
        }
        else if constexpr(N == 3)
        {
            float32x4_t tmp = vld1q_f32(&x[0]);
            return vmaxvq_f32(vsetq_lane_f32(tmp[2], tmp, 3)); 
        }
        else
        {
            return vmaxvq_f32(vld1q_f32(&x[0])); 
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::reduce_max<N, std::enable_if_t<N >= 2 && N <= 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE int call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            return vmaxv_s32(vld1_s32(&x[0]));
        }
        else if constexpr(N == 3)
        {
            int32x4_t tmp = vld1q_s32(&x[0]);
            return vmaxvq_s32(vsetq_lane_s32(tmp[2], tmp, 3)); 
        }
        else
        {
            return vmaxvq_s32(vld1q_s32(&x[0])); 
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::reduce_max<N, std::enable_if_t<N >= 2 && N <= 4, unsigned int>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE unsigned int call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            return vmaxv_u32(vld1_u32(&x[0]));
        }
        else if constexpr(N == 3)
        {
            uint32x4_t tmp = vld1q_u32(&x[0]);
            return vmaxvq_u32(vsetq_lane_u32(tmp[2], tmp, 3)); 
        }
        else
        {
            return vmaxvq_u32(vld1q_u32(&x[0])); 
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::abs<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t tmp = vld1_f32(&x[0]);
            float32x2_t ret = vabs_f32(tmp);
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            float32x4_t tmp = vld1q_f32(&x[0]);
            float32x4_t ret = vabsq_f32(tmp);
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::abs<N, std::enable_if_t<N >= 2 && N <= 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t tmp = vld1_s32(&x[0]);
            int32x2_t ret = vabs_s32(tmp);
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            int32x4_t tmp = vld1q_s32(&x[0]);
            int32x4_t ret = vabsq_s32(tmp);
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::min<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vmin_f32(vld1_f32(&x[0]), vld1_f32(&y[0]));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            float32x4_t ret = vminq_f32(vld1q_f32(&x[0]), vld1q_f32(&y[0]));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::min<N, std::enable_if_t<N >= 2 && N <= 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vmin_s32(vld1_s32(&x[0]), vld1_s32(&y[0]));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            int32x4_t ret = vminq_s32(vld1q_s32(&x[0]), vld1q_s32(&y[0]));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::min<N, std::enable_if_t<N >= 2 && N <= 4, unsigned int>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vmin_u32(vld1_u32(&x[0]), vld1_u32(&y[0]));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            uint32x4_t ret = vminq_u32(vld1q_u32(&x[0]), vld1q_u32(&y[0]));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::max<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vmax_f32(vld1_f32(&x[0]), vld1_f32(&y[0]));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            float32x4_t ret = vmaxq_f32(vld1q_f32(&x[0]), vld1q_f32(&y[0]));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::max<N, std::enable_if_t<N >= 2 && N <= 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t ret = vmax_s32(vld1_s32(&x[0]), vld1_s32(&y[0]));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            int32x4_t ret = vmaxq_s32(vld1q_s32(&x[0]), vld1q_s32(&y[0]));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::max<N, std::enable_if_t<N >= 2 && N <= 4, unsigned int>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t ret = vmax_u32(vld1_u32(&x[0]), vld1_u32(&y[0]));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            uint32x4_t ret = vmaxq_u32(vld1q_u32(&x[0]), vld1q_u32(&y[0]));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::clamp<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t tmp = vmax_f32(vld1_f32(&v[0]), vld1_f32(&min[0]));
            float32x2_t ret = vmin_f32(tmp, vld1_f32(&max[0]));
            return *reinterpret_cast<V*>(&ret); 
        }
        else
        {
            float32x4_t tmp = vmaxq_f32(vld1q_f32(&v[0]), vld1q_f32(&min[0]));
            float32x4_t ret = vminq_f32(tmp, vld1q_f32(&max[0]));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::clamp<N, std::enable_if_t<N >= 2 && N <= 4, int>>
{
    using V = vec<N, int>;
    static CHTHOLLY_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        if constexpr(N == 2)
        {
            int32x2_t tmp = vmax_s32(vld1_s32(&v[0]), vld1_s32(&min[0]));
            int32x2_t ret = vmin_s32(tmp, vld1_s32(&max[0]));
            return *reinterpret_cast<V*>(&ret); 
        }
        else
        {
            int32x4_t tmp = vmaxq_s32(vld1q_s32(&v[0]), vld1q_s32(&min[0]));
            int32x4_t ret = vminq_s32(tmp, vld1q_s32(&max[0]));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::clamp<N, std::enable_if_t<N >= 2 && N <= 4, unsigned int>>
{
    using V = vec<N, unsigned int>;
    static CHTHOLLY_INLINE V call(const V& v, const V& min, const V& max) noexcept
    {
        if constexpr(N == 2)
        {
            uint32x2_t tmp = vmax_u32(vld1_u32(&v[0]), vld1_u32(&min[0]));
            uint32x2_t ret = vmin_u32(tmp, vld1_u32(&max[0]));
            return *reinterpret_cast<V*>(&ret); 
        }
        else
        {
            uint32x4_t tmp = vmaxq_u32(vld1q_u32(&v[0]), vld1q_u32(&min[0]));
            uint32x4_t ret = vminq_u32(tmp, vld1q_u32(&max[0]));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::lerp<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y, float t) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t t_x = vld1_f32(&x[0]);
            float32x2_t t_y = vld1_f32(&y[0]);
            float32x2_t t_t = vdup_n_f32(t);
            float32x2_t ret = vadd_f32(t_x, vmul_f32(t_t, vsub_f32(t_y, t_x)));
            return *reinterpret_cast<V*>(&ret);
        }
        else 
        {
            float32x4_t t_x = vld1q_f32(&x[0]);
            float32x4_t t_y = vld1q_f32(&y[0]);
            float32x4_t t_t = vdupq_n_f32(t);
            float32x4_t ret = vaddq_f32(t_x, vmulq_f32(t_t, vsubq_f32(t_y, t_x)));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::mix<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x, const V& y, const V& t) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t t_x = vld1_f32(&x[0]);
            float32x2_t t_y = vld1_f32(&y[0]);
            float32x2_t t_t = vld1_f32(&t[0]);
            float32x2_t ret = vadd_f32(t_x, vmul_f32(t_t, vsub_f32(t_y, t_x)));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            float32x4_t t_x = vld1q_f32(&x[0]);
            float32x4_t t_y = vld1q_f32(&y[0]);
            float32x4_t t_t = vld1q_f32(&t[0]);
            float32x4_t ret = vaddq_f32(t_x, vmulq_f32(t_t, vsubq_f32(t_y, t_x)));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::recip<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t ret = vdiv_f32(vdup_n_f32(one<float>), vld1_f32(&x[0]));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            float32x4_t ret = vdivq_f32(vdupq_n_f32(one<float>), vld1q_f32(&x[0]));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::step<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& edge, const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t cmp = vclt_f32(vld1_f32(&x[0]), vld1_f32(&edge[0]));
            uint32x2_t tmp = vand_u32(vreinterpret_u32_f32(vdup_n_f32(one<float>)), vreinterpret_u32_f32(cmp));
            float32x2_t ret = vreinterpret_f32_u32(tmp);
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            float32x4_t cmp = vcltq_f32(vld1q_f32(&x[0]), vld1q_f32(&edge[0]));
            uint32x4_t tmp = vandq_u32(vreinterpretq_u32_f32(vdupq_n_f32(one<float>)), vreinterpretq_u32_f32(cmp));
            float32x4_t ret = vreinterpretq_f32_u32(tmp);
            return *reinterpret_cast<V*>(&ret);
        } 
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::smoothstep<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& edge0, const V& edge1, const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t t_edge0 = vld1_f32(&edge0[0]);
            float32x2_t t_edge1 = vld1_f32(&edge1[0]); 
            float32x2_t t_x = vld1_f32(&x[0]);
            float32x2_t tmp = vdiv_f32(vsub_f32(t_x, t_edge0), vsub_f32(t_edge1, t_edge0));
            tmp = vmax_f32(tmp, vdup_n_f32(zero<float>));
            tmp = vmin_f32(tmp, vdup_n_f32(one<float>));
            float32x2_t ret = vmul_f32(vmul_f32(tmp, tmp), vsub_f32(vdup_n_f32(3.f), vmul_f32(vdup_n_f32(2.f), tmp)));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            float32x4_t t_edge0 = vld1q_f32(&edge0[0]);
            float32x4_t t_edge1 = vld1q_f32(&edge1[0]); 
            float32x4_t t_x = vld1q_f32(&x[0]);
            float32x4_t tmp = vdivq_f32(vsubq_f32(t_x, t_edge0), vsubq_f32(t_edge1, t_edge0));
            tmp = vmaxq_f32(tmp, vdupq_n_f32(zero<float>));
            tmp = vminq_f32(tmp, vdupq_n_f32(one<float>));
            float32x4_t ret = vmulq_f32(vmulq_f32(tmp, tmp), vsubq_f32(vdupq_n_f32(3.f), vmulq_f32(vdupq_n_f32(2.f), tmp)));
            return *reinterpret_cast<V*>(&ret);
        } 
    }
};

template<size_t N>
struct ktm::detail::vec_common_implement::fract<N, std::enable_if_t<N >= 2 && N <= 4, float>>
{
    using V = vec<N, float>;
    static CHTHOLLY_INLINE V call(const V& x) noexcept
    {
        if constexpr(N == 2)
        {
            float32x2_t t_x = vld1_f32(&x[0]);
            float32x2_t t_floor = vrndm_f32(t_x);
            float32x2_t ret = vmin_f32(vsub_f32(t_x, t_floor), vdup_n_f32(one<float>));
            return *reinterpret_cast<V*>(&ret);
        }
        else
        {
            float32x4_t t_x = vld1q_f32(&x[0]);
            float32x4_t t_floor = vrndmq_f32(t_x);
            float32x4_t ret = vminq_f32(vsubq_f32(t_x, t_floor), vdupq_n_f32(one<float>));
            return *reinterpret_cast<V*>(&ret);
        }
    }
};

#endif

#endif
