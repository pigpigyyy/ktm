#ifndef _KTM_BASIC_H_
#define _KTM_BASIC_H_

#include "../Basic/Basic.h"
#include "../Acsi/Acsi.h"
#include <limits>

namespace ktm
{

template<typename T>
inline constexpr std::enable_if_t<std::is_arithmetic_v<T>, T> epsilon = std::numeric_limits<T>::epsilon();

template<typename T>
inline constexpr std::enable_if_t<std::is_arithmetic_v<T>, T> zero = static_cast<T>(0);

template<typename T>
inline constexpr std::enable_if_t<std::is_arithmetic_v<T>, T> one = static_cast<T>(1);

template<typename T>
inline constexpr std::enable_if_t<std::is_arithmetic_v<T>, T> ex = static_cast<T>(2.718281828459045);

template<typename T>
inline constexpr std::enable_if_t<std::is_arithmetic_v<T>, T> pi = static_cast<T>(3.141592653589793);

template<typename T>
inline constexpr std::enable_if_t<std::is_arithmetic_v<T>, T> tow_pi = static_cast<T>(2) * pi<T>;

template<typename T>
inline constexpr std::enable_if_t<std::is_arithmetic_v<T>, T> half_pi = static_cast<T>(0.5) * pi<T>;

template<typename T>
inline constexpr std::enable_if_t<std::is_arithmetic_v<T>, T> one_over_pi = one<T> / pi<T>;

// 定义vector
template<size_t N, typename T, typename = std::enable_if_t<(N > 0) && std::is_arithmetic_v<T>>> struct vec;

// 定义matrix, Row为行的长度, Col为列的长度
template<size_t Row, size_t Col, typename T, typename = std::enable_if_t<(Row > 1) && (Col > 1) && std::is_arithmetic_v<T>>> struct mat;

// 定义quaternion
template<typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>> struct quat;

}

#endif