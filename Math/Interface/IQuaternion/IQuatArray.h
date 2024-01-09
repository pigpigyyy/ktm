#ifndef _I_QUAT_ARRAY_H_
#define _I_QUAT_ARRAY_H_

#include "../../type/basic.h"
#include <array>

namespace ktm
{
template<class Father, class Child>
struct IQuatArray;

template<class Father,typename T>
struct IQuatArray<Father, quat<T>> : Father
{
    using Father::Father;
    using array_type = std::array<T, 4>;
};
}

#endif