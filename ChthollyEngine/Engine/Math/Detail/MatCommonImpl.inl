#ifndef _MAT_COMMON_IMPL_INL_
#define _MAT_COMMON_IMPL_INL_

#include "Math/MathType/BaseType.h"
#include "MatCommonImpl.h"

template<size_t Col, size_t Row, typename T>
struct ktm::detail::mat_common_implement::transpose
{
	using M = mat<Col, Row, T>;
    using RetM = mat_traits_tp_t<M>;
    using ColV = mat_traits_col_t<M>;
    using RowV = mat_traits_row_t<M>;
    static CHTHOLLY_INLINE RetM call(const M& m) noexcept
    {
        return call(m, std::make_index_sequence<mat_traits_col_n<M>>(), std::make_index_sequence<mat_traits_row_n<M>>());
    }
private:
    template<size_t ...Rs, size_t ...Cs>
    static CHTHOLLY_INLINE RetM call(const M& m, std::index_sequence<Rs...>, std::index_sequence<Cs...>) noexcept
    {
        RetM ret;
        size_t row_index;
        ((row_index = Rs, reinterpret_cast<RowV*>(&ret)[Rs] = RowV(reinterpret_cast<const float*>(&reinterpret_cast<const ColV*>(&m)[Cs])[row_index]...)), ...);
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::mat_common_implement::determinant<N, N, T>
{
    static_assert(N >= 2 && N <= 4);
    using M = mat<N, N, T>;
    using ColT = mat_traits_col_t<M>;
    static CHTHOLLY_INLINE T call(const M& m) noexcept
    {
        if constexpr(N == 2)
        {
            return reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] *
                   reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1] -
                   reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
                   reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1];
                   
        }
        else if constexpr(N == 3)
        {
            return reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] *
                  (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1] *
                   reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2] -
                   reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1] *
                   reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2])
                   +
                   reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
                  (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1] *
                   reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[2] -
                   reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1] *
                   reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2])
                   +
                   reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] *
                  (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1] *
                   reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2] -
                   reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1] *
                   reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[2]);
        }
        else if constexpr(N == 4)
        {
            T d00 = reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2] *
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[3] -
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[2] *
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[3];
            
            T d01 = reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[2] *
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[3] -
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2] *
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[3];

            T d02 = reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2] *
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[3] -
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2] *
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[3];

            T r0 =  reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1] * d00 +
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1] * d01 + 
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[1] * d02;
            
            T r1 =  reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] * d00 +
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] * d01 + 
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[0] * d02;

            T d10 = reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] *
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[1] -
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[0] *
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1];

            T d11 = reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[0] *
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1] -
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[1];

            T d12 = reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1] -
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] *
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1];

            T r2 =  reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[3] * d10 +
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[3] * d11 +
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[3] * d12;

            T r3 =  reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2] * d10 +
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2] * d11 +
                    reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[2] * d12;
                   
            return reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] * r0 -
                   reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1] * r1 +
                   reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[2] * r2 -
                   reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[3] * r3;
        }
    }
};

template<size_t N, typename T>
struct ktm::detail::mat_common_implement::inverse<N, N, T>
{
    static_assert(N >= 2 && N <= 4 && std::is_floating_point_v<T>);
    using M = mat<N, N, T>;
    using ColT = mat_traits_col_t<M>;
    static CHTHOLLY_INLINE M call(const M& m) noexcept
    {
        T one_over_det = one<T> / determinant<N, N, T>::call(m);
        M ret;
        if constexpr(N == 2)
        {
            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[0])[0] = reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1] * one_over_det;
            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[0])[1] = - reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] * one_over_det; 
            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[1])[0] = - reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1] * one_over_det; 
            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[1])[1] = reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] * one_over_det; 
        }
        if constexpr(N == 3)
        {
            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[0])[0] = one_over_det *
                (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1] *
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2] -
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1] *
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2]);

            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[0])[1] = one_over_det *
                (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1] *
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[2] -
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1] *
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2]);

            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[0])[2] = one_over_det *
                (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1] *
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2] -
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1] *
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[2]);

            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[1])[0] = one_over_det *
                (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] *
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2] -
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2]);
            
            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[1])[1] = one_over_det *
                (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] *
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2] -
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] *
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[2]);

            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[1])[2] = one_over_det *
                (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[2] -
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] *
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2]);

            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[2])[0] = one_over_det *
                (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1] -
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] *
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1]);

            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[2])[1] = one_over_det *
                (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] *
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1] -
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] *
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1]);

            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[2])[2] = one_over_det *
                (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] *
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1] -
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
                 reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1]);
        }
        else
        {
            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[0])[0] = one_over_det * 
            (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[3] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[2] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[3] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[2] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[3] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2]);

            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[0])[1] = one_over_det * 
            (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[3] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[2] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[3] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[2] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[3]);

            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[0])[2] = one_over_det * 
            (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[3] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[2] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[3] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[2] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[3] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2]);

            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[0])[3] = one_over_det * 
            (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[3] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[3] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[3]);           
        
            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[1])[0] = one_over_det * 
            (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[3] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[2] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[3] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[2] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[3]);

            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[1])[1] = one_over_det * 
            (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[3] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[2] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[3] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[2] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[3] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2]); 
        
            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[1])[2] = one_over_det * 
            (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[3] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[2] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[3] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[2] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[3]); 
        
            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[1])[3] = one_over_det * 
            (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[3] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[3] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[3] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2]); 
       
            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[2])[0] = one_over_det * 
            (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[3] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[1] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[3] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[1] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[3] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1]); 

            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[2])[1] = one_over_det * 
            (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[3] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[1] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[3] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[1] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[3]); 

            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[2])[2] = one_over_det * 
            (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[3] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[1] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[3] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[1] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[3] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1]); 
        
            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[2])[3] = one_over_det * 
            (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[3] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[3] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[3] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[3]); 

            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[3])[0] = one_over_det * 
            (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[1] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[2] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[1] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[2]); 

            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[3])[1] = one_over_det * 
            (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[2] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[1] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[2] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[1] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1]); 
                    
            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[3])[2] = one_over_det * 
            (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[1] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[2] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[1] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[3])[2]);
    
            reinterpret_cast<T*>(&reinterpret_cast<ColT*>(&ret)[3])[3] = one_over_det * 
            (reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[2] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[1] +
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[1] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[2] -
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[2])[0] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[0])[2] *
             reinterpret_cast<const T*>(&reinterpret_cast<const ColT*>(&m)[1])[1]);
        }
        return ret;
    }
};

template<size_t N, typename T>
struct ktm::detail::mat_common_implement::trace<N, N, T>
{
    static_assert(N >= 2 && N <= 4);
    using M = mat<N, N, T>;
    using ColV = mat_traits_col_t<M>;
    static CHTHOLLY_INLINE T call(const M& m) noexcept
    {
        return call(m, std::make_index_sequence<N>());
    }
private:
    template<size_t ...Ns>
    static CHTHOLLY_INLINE T call(const M& m, std::index_sequence<Ns...>) noexcept
    {
        return ((reinterpret_cast<const T*>(&reinterpret_cast<const ColV*>(&m)[Ns])[Ns])+ ...);
    }
};
#endif
