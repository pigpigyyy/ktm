#ifndef _QUATERNION_SIMD_INL_
#define _QUATERNION_SIMD_INL_

#include "QuatOptFwd.h"
#include "Math/Library/Definition.h"

#if defined(CHTHOLLY_SIMD_NEON)

template<>
struct ktm::detail::quat_opt_implement::mul<float>
{
    using Q = quat<float>;
    static CHTHOLLY_INLINE Q call(const Q& x, const Q& y) noexcept
    {
        float32x4_t t_y = vld1q_f32(&y[0]);
        float32x4_t t_y_opp = vnegq_f32(t_y);

        float32x4_t tmp_0 = _neon_shuffleq_f32(t_y, t_y_opp, 3, 2, 3, 2);
        float32x4_t tmp_1 = _neon_shuffleq_f32(t_y, t_y_opp, 1, 1, 0, 0); 

        float32x4_t mul_x = _neon_shuffleq_f32(tmp_1, tmp_0, 0, 3, 0, 2); 
        float32x4_t mul_y = _neon_shuffleq_f32(tmp_0, tmp_1, 2, 0, 1, 2); 
        float32x4_t mul_z = _neon_shuffleq_f32(t_y_opp, t_y, 0, 1, 2, 3);

        float32x4_t add_0 = vmulq_f32(vdupq_n_f32(x[0]), t_y); 
        float32x4_t add_1 = vmulq_f32(vdupq_n_f32(x[1]), mul_x); 
        float32x4_t add_2 = vmulq_f32(vdupq_n_f32(x[2]), mul_y); 
        float32x4_t add_3 = vmulq_f32(vdupq_n_f32(x[3]), mul_z); 

        float32x4_t ret = vaddq_f32_all(add_0, add_1, add_2, add_3);

        return *reinterpret_cast<Q*>(&ret);
    }
};

template<>
struct ktm::detail::quat_opt_implement::mul_to_self<float>
{
    using Q = quat<float>;
    static CHTHOLLY_INLINE void call(Q& x, const Q& y) noexcept
    {
        float32x4_t t_y = vld1q_f32(&y[0]);
        float32x4_t t_y_opp = vnegq_f32(t_y);

        float32x4_t tmp_0 = _neon_shuffleq_f32(t_y, t_y_opp, 3, 2, 3, 2);
        float32x4_t tmp_1 = _neon_shuffleq_f32(t_y, t_y_opp, 1, 1, 0, 0); 

        float32x4_t mul_x = _neon_shuffleq_f32(tmp_1, tmp_0, 0, 3, 0, 2); 
        float32x4_t mul_y = _neon_shuffleq_f32(tmp_0, tmp_1, 2, 0, 1, 2); 
        float32x4_t mul_z = _neon_shuffleq_f32(t_y_opp, t_y, 0, 1, 2, 3);

        float32x4_t add_0 = vmulq_f32(vdupq_n_f32(x[0]), t_y); 
        float32x4_t add_1 = vmulq_f32(vdupq_n_f32(x[1]), mul_x); 
        float32x4_t add_2 = vmulq_f32(vdupq_n_f32(x[2]), mul_y); 
        float32x4_t add_3 = vmulq_f32(vdupq_n_f32(x[3]), mul_z); 

        float32x4_t ret = vaddq_f32_all(add_0, add_1, add_2, add_3);

        vst1q_f32(&x[0], ret);
    }
};

#endif

#endif