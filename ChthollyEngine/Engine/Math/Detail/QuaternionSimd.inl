#ifndef _QUATERNION_SIMD_INL_
#define _QUATERNION_SIMD_INL_

#include "QuatOptFwd.h"
#include "Math/Library/ArtcBase.h"

#if defined(CHTHOLLY_SIMD_NEON)

namespace ktm
{
namespace detail
{
namespace quat_opt_implement
{
CHTHOLLY_FUNC float32x4_t mul_qq(float32x4_t x, float32x4_t y) noexcept
{
    float32x4_t y_opp = vnegq_f32(y);

    float32x4_t tmp_0 = acsi_vshuffleq_f32(y, y_opp, 2, 2, 3, 3);
    float32x4_t tmp_1 = acsi_vshuffleq_f32(y, y_opp, 1, 0, 1, 0); 

    float32x4_t mul_x = acsi_vshuffleq_f32(tmp_0, tmp_1, 2, 1, 3, 0); 
    float32x4_t mul_y = acsi_vshuffleq_f32(y, y_opp, 1, 0, 3, 2); 
    float32x4_t mul_z = acsi_vshuffleq_f32(tmp_1, tmp_0, 2, 1, 0, 3);

    float32x4_t add_0 = vmulq_f32(vdupq_n_f32(vgetq_lane_f32(x, 0)), mul_x); 
    float32x4_t add_1 = vmulq_f32(vdupq_n_f32(vgetq_lane_f32(x, 1)), mul_y); 
    float32x4_t add_2 = vmulq_f32(vdupq_n_f32(vgetq_lane_f32(x, 2)), mul_z); 
    float32x4_t add_3 = vmulq_f32(vdupq_n_f32(vgetq_lane_f32(x, 3)), y); 

    return acsi_vaddq_f32_all(add_0, add_1, add_2, add_3); 
}

CHTHOLLY_FUNC float32x4_t mul_vq(float32x4_t v, float32x4_t q) noexcept
{
    float32x4_t q_opp = vnegq_f32(q);

    float32x4_t tmp_0 = acsi_vshuffleq_f32(q, q_opp, 2, 2, 3, 3);
    float32x4_t tmp_1 = acsi_vshuffleq_f32(q, q_opp, 1, 0, 1, 0); 

    float32x4_t mul_x = acsi_vshuffleq_f32(tmp_0, tmp_1, 2, 1, 3, 0); 
    float32x4_t mul_y = acsi_vshuffleq_f32(q, q_opp, 1, 0, 3, 2); 
    float32x4_t mul_z = acsi_vshuffleq_f32(tmp_1, tmp_0, 2, 1, 0, 3);

    float32x4_t add_0 = vmulq_f32(vdupq_n_f32(vgetq_lane_f32(v, 0)), mul_x); 
    float32x4_t add_1 = vmulq_f32(vdupq_n_f32(vgetq_lane_f32(v, 1)), mul_y); 
    float32x4_t add_2 = vmulq_f32(vdupq_n_f32(vgetq_lane_f32(v, 2)), mul_z); 

    return acsi_vaddq_f32_all(add_0, add_1, add_2); 
}
}
}
}

template<>
struct ktm::detail::quat_opt_implement::mul<float>
{
    using Q = quat<float>;
    static CHTHOLLY_INLINE Q call(const Q& x, const Q& y) noexcept
    {
        float32x4_t t_x = vld1q_f32(&x[0]);
        float32x4_t t_y = vld1q_f32(&y[0]);
        float32x4_t ret = mul_qq(t_x, t_y);
        return *reinterpret_cast<Q*>(&ret);
    }
};

template<>
struct ktm::detail::quat_opt_implement::mul_to_self<float>
{
    using Q = quat<float>;
    static CHTHOLLY_INLINE void call(Q& x, const Q& y) noexcept
    {
        float32x4_t t_x = vld1q_f32(&x[0]);
        float32x4_t t_y = vld1q_f32(&y[0]);
        float32x4_t ret = mul_qq(t_x, t_y);
        vst1q_f32(&x[0], ret);
    }
};

template<>
struct ktm::detail::quat_opt_implement::act<float>
{
    using Q = quat<float>;
    static CHTHOLLY_INLINE vec<3, float> call(const Q& q, const vec<3, float>& v) noexcept
    {
        // |q| = 1 => q-1 <==> qc
        // q * quat(v,0) * qc
        float32x4_t t_q = vld1q_f32(&q[0]);
        float32x4_t t_qi = vmulq_f32(t_q, vsetq_lane_f32(one<float>, vdupq_n_f32(-one<float>), 3));
        float32x4_t t_v = vld1q_f32(&v[0]);
        float32x4_t ret = mul_qq(t_q, mul_vq(t_v, t_qi));

        return *reinterpret_cast<vec<3, float>*>(&ret);
    }
};

#elif defined(CHTHOLLY_SIMD_SSE) 

template<>
struct ktm::detail::quat_opt_implement::mul<float>
{
    using Q = quat<float>;
    static CHTHOLLY_INLINE Q call(const Q& x, const Q& y) noexcept
    {
        __m128 t_y = _mm_load_ps(&y[0]);
        __m128 t_y_opp = acsi_mm_neg_ps(t_y);

        __m128 tmp_0 = _mm_shuffle_ps(t_y, t_y_opp, _MM_SHUFFLE(2, 2, 3, 3));
        __m128 tmp_1 = _mm_shuffle_ps(t_y, t_y_opp, _MM_SHUFFLE(1, 0, 1, 0)); 

        __m128 mul_x = _mm_shuffle_ps(tmp_0, tmp_1, _MM_SHUFFLE(2, 1, 3, 0)); 
        __m128 mul_y = _mm_shuffle_ps(t_y, t_y_opp, _MM_SHUFFLE(1, 0, 3, 2)); 
        __m128 mul_z = _mm_shuffle_ps(tmp_1, tmp_0, _MM_SHUFFLE(2, 1, 0, 3));

        __m128 add_0 = _mm_mul_ps(_mm_set1_ps(x[0]), mul_x); 
        __m128 add_1 = _mm_mul_ps(_mm_set1_ps(x[1]), mul_y); 
        __m128 add_2 = _mm_mul_ps(_mm_set1_ps(x[2]), mul_z); 
        __m128 add_3 = _mm_mul_ps(_mm_set1_ps(x[3]), t_y); 

        __m128 ret = acsi_mm_add_ps_all(add_0, add_1, add_2, add_3);

        return *reinterpret_cast<Q*>(&ret);
    }
};

template<>
struct ktm::detail::quat_opt_implement::mul_to_self<float>
{
    using Q = quat<float>;
    static CHTHOLLY_INLINE void call(Q& x, const Q& y) noexcept
    {
        __m128 t_y = _mm_load_ps(&y[0]);
        __m128 t_y_opp = acsi_mm_neg_ps(t_y);

        __m128 tmp_0 = _mm_shuffle_ps(t_y, t_y_opp, _MM_SHUFFLE(2, 2, 3, 3));
        __m128 tmp_1 = _mm_shuffle_ps(t_y, t_y_opp, _MM_SHUFFLE(1, 0, 1, 0)); 

        __m128 mul_x = _mm_shuffle_ps(tmp_0, tmp_1, _MM_SHUFFLE(2, 1, 3, 0)); 
        __m128 mul_y = _mm_shuffle_ps(t_y, t_y_opp, _MM_SHUFFLE(1, 0, 3, 2)); 
        __m128 mul_z = _mm_shuffle_ps(tmp_1, tmp_0, _MM_SHUFFLE(2, 1, 0, 3));

        __m128 add_0 = _mm_mul_ps(_mm_set1_ps(x[0]), mul_x); 
        __m128 add_1 = _mm_mul_ps(_mm_set1_ps(x[1]), mul_y); 
        __m128 add_2 = _mm_mul_ps(_mm_set1_ps(x[2]), mul_z); 
        __m128 add_3 = _mm_mul_ps(_mm_set1_ps(x[3]), t_y);

        __m128 ret = acsi_mm_add_ps_all(add_0, add_1, add_2, add_3);

        _mm_store_ps(&x[0], ret);
    }
};

#endif

#endif