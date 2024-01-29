#ifndef _KTM_QUAT_CALC_SIMD_INL_
#define _KTM_QUAT_CALC_SIMD_INL_

#include "quat_calc_fwd.h"
#include "../../simd/intrin.h"

#if defined(KTM_SIMD_ARM)

template<>
struct ktm::detail::quat_calc_implement::mul<float>
{
    using Q = quat<float>;
    static KTM_INLINE Q call(const Q& x, const Q& y) noexcept
    {
        Q ret;
        ret.vector.st = arm::qt::fq_mul_fq(x.vector.st, y.vector.st);
        return ret;
    }
};

template<>
struct ktm::detail::quat_calc_implement::mul_to_self<float>
{
    using Q = quat<float>;
    static KTM_INLINE void call(Q& x, const Q& y) noexcept
    {
        x.vector.st = arm::qt::fq_mul_fq(x.vector.st, y.vector.st);
    }
};

template<>
struct ktm::detail::quat_calc_implement::act<float>
{
    using Q = quat<float>;
    static KTM_INLINE vec<3, float> call(const Q& q, const vec<3, float>& v) noexcept
    {
        // |q| = 1 => q-1 <==> qc
        // q * quat(v,0) * qc
        vec<3, float> ret;
        float32x4_t qi = vmulq_f32(q.vector.st, vsetq_lane_f32(1.f, vdupq_n_f32(-1.f), 3));
        ret.st = arm::qt::fq_mul_fq(q.vector.st, arm::qt::fv3_mul_fq(v.st, qi));
        return ret;
    }
};

#elif defined(KTM_SIMD_X86) 

template<>
struct ktm::detail::quat_calc_implement::mul<float>
{
    using Q = quat<float>;
    static KTM_INLINE Q call(const Q& x, const Q& y) noexcept
    {
        Q ret;
        ret.vector.st = x86::qt::fq_mul_fq(x.vector.st, y.vector.st);
        return ret;
    }
};

template<>
struct ktm::detail::quat_calc_implement::mul_to_self<float>
{
    using Q = quat<float>;
    static KTM_INLINE void call(Q& x, const Q& y) noexcept
    {
        x.vector.st = x86::qt::fq_mul_fq(x.vector.st, y.vector.st);
    }
};

template<>
struct ktm::detail::quat_calc_implement::act<float>
{
    using Q = quat<float>;
    static KTM_INLINE vec<3, float> call(const Q& q, const vec<3, float>& v) noexcept
    {
        vec<3, float> ret;
        __m128 qi = _mm_mul_ps(q.vector.st, _mm_set_ps(1.f, -1.f, -1.f, -1.f));
        ret.st = x86::qt::fq_mul_fq(q.vector.st, x86::qt::fv3_mul_fq(v.st, qi));
        return ret;
    }
};

#endif

#endif