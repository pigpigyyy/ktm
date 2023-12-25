#ifndef _NEON_EX_H_
#define _NEON_EX_H_

#include "SetupAcsi.h"
#include <cstddef>

#if defined(CHTHOLLY_SIMD_NEON)

#if defined(CHTHOLLY_COMPILER_CLANG)

#define neon_vshuffle_s32(a, b, s2, s1) neon_vshuffle_f32(a, b, s2, s1)
#define neon_vshuffleq_s32(a, b, s4, s3, s2, s1) neon_vshuffleq_f32(a, b, s4, s3, s2, s1)
#define neon_vshuffle_f32(a, b, s2, s1) __builtin_shufflevector(a, b, s1, (s2) + 2)
#define neon_vshuffleq_f32(a, b, s4, s3, s2, s1) __builtin_shufflevector(a, b, s1, s2, (s3) + 4, (s4) + 4)

#else

#define neon_vshuffle_s32(a, b, s2, s1) vcopy_lane_s32(vmov_n_s32(vget_lane_s32(a, s1)), 1, b, s2)
#define neon_vshuffleq_s32(a, b, s4, s3, s2, s1) vcopyq_laneq_s32(vcopyq_laneq_s32(vcopyq_laneq_s32(vmovq_n_s32(vgetq_lane_s32(a, s1)), 1, a, s2), 2, b, s3), 3, b, s4)
#define neon_vshuffle_f32(a, b, s2, s1) vcopy_lane_f32(vmov_n_f32(vget_lane_f32(a, s1)), 1, b, s2)
#define neon_vshuffleq_f32(a, b, s4, s3, s2, s1) vcopyq_laneq_f32(vcopyq_laneq_f32(vcopyq_laneq_f32(vmovq_n_f32(vgetq_lane_f32(a, s1)), 1, a, s2), 2, b, s3), 3, b, s4)

#endif

namespace neon
{
CHTHOLLY_FUNC int vandv_s32(int32x2_t x) noexcept
{
	return vget_lane_s32(x, 0) & vget_lane_s32(x, 1);
}

CHTHOLLY_FUNC int vandvq_s32(int32x4_t x) noexcept
{
	return vandv_s32(vand_s32(vget_low_s32(x), vget_high_s32(x)));
}

CHTHOLLY_FUNC int32x2_t vclamp_s32(int32x2_t x, int32x2_t min, int32x2_t max) noexcept
{
	return vmin_s32(vmax_s32(x, min), max);
}

CHTHOLLY_FUNC int32x4_t vclampq_s32(int32x4_t x, int32x4_t min, int32x4_t max) noexcept
{
	return vminq_s32(vmaxq_s32(x, min), max);
}

CHTHOLLY_FUNC int32x2_t vdot_s32(int32x2_t x, int32x2_t y) noexcept
{
	int32x2_t mul = vmul_s32(x, y);
	return vpadd_s32(mul, mul);
}

CHTHOLLY_FUNC int32x4_t vdotq_s32(int32x4_t x, int32x4_t y) noexcept
{
	int32x4_t mul = vmulq_s32(x, y);
    int32x4_t add_0 = vpaddq_s32(mul, mul);
    int32x4_t add_1 = vpaddq_s32(add_0, add_0);
	return add_1;
}

CHTHOLLY_FUNC int vdotv_s32(int32x2_t x, int32x2_t y) noexcept
{
	return vaddv_s32(vmul_s32(x, y));
}

template<size_t N>
CHTHOLLY_FUNC int vdotvq_s32(int32x4_t x, int32x4_t y) noexcept;

template<>
CHTHOLLY_FUNC int vdotvq_s32<3>(int32x4_t x, int32x4_t y) noexcept
{
	int32x4_t mul = vmulq_s32(x, y);
	return vaddvq_s32(vsetq_lane_s32(0, mul, 3));	
}

template<>
CHTHOLLY_FUNC int vdotvq_s32<4>(int32x4_t x, int32x4_t y) noexcept
{
	return vaddvq_s32(vmulq_s32(x, y));	
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC int32x2_t vadd_s32_all(SimdT arg, SimdTs... args) noexcept
{
	return vadd_s32(arg, vadd_s32_all(args...));
}

template<>
CHTHOLLY_FUNC int32x2_t vadd_s32_all<int32x2_t>(int32x2_t arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC int32x2_t vmul_s32_all(SimdT arg, SimdTs... args) noexcept
{
	return vmul_s32(arg, vmul_s32_all(args...));
}

template<>
CHTHOLLY_FUNC int32x2_t vmul_s32_all<int32x2_t>(int32x2_t arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC int32x4_t vaddq_s32_all(SimdT arg, SimdTs... args) noexcept
{
	return vaddq_s32(arg, vaddq_s32_all(args...));
}

template<>
CHTHOLLY_FUNC int32x4_t vaddq_s32_all<int32x4_t>(int32x4_t arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC int32x4_t vmulq_s32_all(SimdT arg, SimdTs... args) noexcept
{
	return vmulq_s32(arg, vmulq_s32_all(args...));
}

template<>
CHTHOLLY_FUNC int32x4_t vmulq_s32_all<int32x4_t>(int32x4_t arg) noexcept
{
	return arg;
}

CHTHOLLY_FUNC float vandv_f32(float32x2_t x) noexcept
{
	const union { int i; float f; } ret = { vandv_s32(vreinterpret_s32_f32(x)) };
	return ret.f;
}

CHTHOLLY_FUNC float vandvq_f32(float32x4_t x) noexcept
{
	const union { int i; float f; } ret = { vandvq_s32(vreinterpretq_s32_f32(x)) };
	return ret.f;
}

CHTHOLLY_FUNC float32x2_t vclamp_f32(float32x2_t x, float32x2_t min, float32x2_t max) noexcept
{
	return vmin_f32(vmax_f32(x, min), max);
}

CHTHOLLY_FUNC float32x4_t vclampq_f32(float32x4_t x, float32x4_t min, float32x4_t max) noexcept
{
	return vminq_f32(vmaxq_f32(x, min), max);
}

CHTHOLLY_FUNC float32x2_t vdot_f32(float32x2_t x, float32x2_t y) noexcept
{
	float32x2_t mul = vmul_f32(x, y);
	return vpadd_f32(mul, mul);
}

CHTHOLLY_FUNC float32x4_t vdotq_f32(float32x4_t x, float32x4_t y) noexcept
{
	float32x4_t mul = vmulq_f32(x, y);
    float32x4_t add_0 = vpaddq_f32(mul, mul);
    float32x4_t add_1 = vpaddq_f32(add_0, add_0);
	return add_1;
}

CHTHOLLY_FUNC float vdotv_f32(float32x2_t x, float32x2_t y) noexcept
{
	return vaddv_f32(vmul_f32(x, y));
}

template<size_t N>
CHTHOLLY_FUNC float vdotvq_f32(float32x4_t x, float32x4_t y) noexcept;

template<>
CHTHOLLY_FUNC float vdotvq_f32<3>(float32x4_t x, float32x4_t y) noexcept
{
	float32x4_t mul = vmulq_f32(x, y);
	return vaddvq_f32(vsetq_lane_f32(0.f, mul, 3));	
}

template<>
CHTHOLLY_FUNC float vdotvq_f32<4>(float32x4_t x, float32x4_t y) noexcept
{
	return vaddvq_f32(vmulq_f32(x, y));	
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC float32x2_t vadd_f32_all(SimdT arg, SimdTs... args) noexcept
{
	return vadd_f32(arg, vadd_f32_all(args...));
}

template<>
CHTHOLLY_FUNC float32x2_t vadd_f32_all<float32x2_t>(float32x2_t arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC float32x2_t vmul_f32_all(SimdT arg, SimdTs... args) noexcept
{
	return vmul_f32(arg, vmul_f32_all(args...));
}

template<>
CHTHOLLY_FUNC float32x2_t vmul_f32_all<float32x2_t>(float32x2_t arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC float32x4_t vaddq_f32_all(SimdT arg, SimdTs... args) noexcept
{
	return vaddq_f32(arg, vaddq_f32_all(args...));
}

template<>
CHTHOLLY_FUNC float32x4_t vaddq_f32_all<float32x4_t>(float32x4_t arg) noexcept
{
	return arg;
}

template<typename SimdT, typename ...SimdTs>
CHTHOLLY_FUNC float32x4_t vmulq_f32_all(SimdT arg, SimdTs... args) noexcept
{
	return vmulq_f32(arg, vmulq_f32_all(args...));
}

template<>
CHTHOLLY_FUNC float32x4_t vmulq_f32_all<float32x4_t>(float32x4_t arg) noexcept
{
	return arg;
}
}

#endif

#endif