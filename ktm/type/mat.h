//  MIT License
//
//  Copyright (c) 2023 有个小小杜
//
//  Created by 有个小小杜
//

#ifndef _KTM_MAT_H_
#define _KTM_MAT_H_

#include "vec.h"
#include "../traits/type_single_extends.h"
#include "../interface/shared/iarray_util.h"
#include "../interface/shared/iarray_io.h"
#include "../interface/shared/iarray_init.h"
#include "../interface/matrix/imat_data.h"
#include "../interface/matrix/imat_make.h"
#include "../interface/matrix/imat_array.h"
#include "../interface/matrix/imat_calc.h"

namespace ktm
{

template<class Child>
using mat_father_type = single_extends_t<Child, iarray_init, imat_data, imat_make, imat_array, imat_calc, iarray_io, iarray_util>;

template<size_t Row, size_t Col, typename T>
struct mat<Row, Col, T> : mat_father_type<mat<Row, Col, T>>
{
    using fater_type = mat_father_type<mat<Row, Col, T>>;
    using fater_type::fater_type;
};

}

#include "../detail/matrix/mat_calc.inl"
#include "../detail/matrix/mat_calc_simd.inl"

#endif