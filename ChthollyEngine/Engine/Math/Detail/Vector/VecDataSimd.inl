#ifndef _VEC_DATA_SIMD_INL_
#define _VEC_DATA_SIMD_INL_

#include "VecDataFwd.h"
#include "Math/Library/ArtcBase.h"

#if defined(CHTHOLLY_SIMD_NEON)

template<>
struct ktm::detail::vec_data_implement::vec_storage<2, float>
{
    typedef float32x2_t type;
};

template<>
struct ktm::detail::vec_data_implement::vec_storage<3, float>
{
    typedef float32x4_t type;
};

template<>
struct ktm::detail::vec_data_implement::vec_storage<4, float>
{
    typedef float32x4_t type;
};

template<size_t S0, size_t S1>
struct ktm::detail::vec_data_implement::vec_swizzle<2, 2, float, S0, S1>
{
    using V = vec<2, float>;
    using RetV = vec<2, float>;
    static CHTHOLLY_INLINE RetV call(const V& v) noexcept
    {
        RetV ret;
        ret.st = neon_shuffle_f32(v.st, v.st, S1, S0);
        return ret;
    }
};

template<size_t IN, size_t S0, size_t S1>
struct ktm::detail::vec_data_implement::vec_swizzle<2, IN, std::enable_if_t<IN == 3 || IN == 4, float>, S0, S1>
{
    using V = vec<IN, float>;
    using RetV = vec<2, float>;
    static CHTHOLLY_INLINE RetV call(const V& v) noexcept
    {
        RetV ret;
        ret.st = vcopy_laneq_f32(ret.st, 0, v.st, S0);
        ret.st = vcopy_laneq_f32(ret.st, 1, v.st, S1); 
        return ret;
    }
};

template<size_t IN, size_t S0, size_t S1, size_t S2>
struct ktm::detail::vec_data_implement::vec_swizzle<3, IN, std::enable_if_t<IN == 3 || IN == 4, float>, S0, S1, S2>
{
    using V = vec<IN, float>;
    using RetV = vec<3, float>;
    static CHTHOLLY_INLINE RetV call(const V& v) noexcept
    {
        RetV ret;
        ret.st = neon_shuffleq_f32(v.st, v.st, 3, S2, S1, S0);
        return ret;
    }
};

template<size_t S0, size_t S1, size_t S2, size_t S3>
struct ktm::detail::vec_data_implement::vec_swizzle<4, 4, float, S0, S1, S2, S3>
{
    using V = vec<4, float>;
    using RetV = vec<4, float>;
    static CHTHOLLY_INLINE RetV call(const V& v) noexcept
    {
        RetV ret;
        ret.st = neon_shuffleq_f32(v.st, v.st, S3, S2, S1, S0);
        return ret;
    }
};

template<>
struct ktm::detail::vec_data_implement::vec_storage<2, int>
{
    typedef int32x2_t type;
};

template<>
struct ktm::detail::vec_data_implement::vec_storage<3, int>
{
    typedef int32x4_t type;
};

template<>
struct ktm::detail::vec_data_implement::vec_storage<4, int>
{
    typedef int32x4_t type;
};

template<size_t S0, size_t S1>
struct ktm::detail::vec_data_implement::vec_swizzle<2, 2, int, S0, S1>
{
    using V = vec<2, int>;
    using RetV = vec<2, int>;
    static CHTHOLLY_INLINE RetV call(const V& v) noexcept
    {
        RetV ret;
        ret.st = neon_shuffle_s32(v.st, v.st, S1, S0);
        return ret;
    }
};

template<size_t IN, size_t S0, size_t S1>
struct ktm::detail::vec_data_implement::vec_swizzle<2, IN, std::enable_if_t<IN == 3 || IN == 4, int>, S0, S1>
{
    using V = vec<IN, int>;
    using RetV = vec<2, int>;
    static CHTHOLLY_INLINE RetV call(const V& v) noexcept
    {
        RetV ret;
        ret.st = vcopy_laneq_s32(ret.st, 0, v.st, S0);
        ret.st = vcopy_laneq_s32(ret.st, 1, v.st, S1); 
        return ret;
    }
};

template<size_t IN, size_t S0, size_t S1, size_t S2>
struct ktm::detail::vec_data_implement::vec_swizzle<3, IN, std::enable_if_t<IN == 3 || IN == 4, int>, S0, S1, S2>
{
    using V = vec<IN, int>;
    using RetV = vec<3, int>;
    static CHTHOLLY_INLINE RetV call(const V& v) noexcept
    {
        RetV ret;
        ret.st = neon_shuffleq_s32(v.st, v.st, 3, S2, S1, S0);
        return ret;
    }
};

template<size_t S0, size_t S1, size_t S2, size_t S3>
struct ktm::detail::vec_data_implement::vec_swizzle<4, 4, int, S0, S1, S2, S3>
{
    using V = vec<4, int>;
    using RetV = vec<4, int>;
    static CHTHOLLY_INLINE RetV call(const V& v) noexcept
    {
        RetV ret;
        ret.st = neon_shuffleq_s32(v.st, v.st, S3, S2, S1, S0);
        return ret;
    }
};

#endif

#endif