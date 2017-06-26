// Copyright (c) 2017 Sony Corporation. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/** Sigmoid
 */
#ifndef __NBLA_FUNCTION_SIGMOID_HPP__
#define __NBLA_FUNCTION_SIGMOID_HPP__

#include <nbla/function/utils/base_transform_unary.hpp>

#include <cmath>

namespace nbla {

/** @class Sigmoid
@brief Elementwise Sigmoid function defined as
@f[
y_i = \frac{1}{1 + \exp(-x_i)}.
@f]

Inputs:
- N-D array.

Outputs:
- N-D array.

@tparam T Data type for computation.
\ingroup FunctionImplGrp
 */
NBLA_DEFINE_TRANSFORM_UNARY(Sigmoid, (T)1 / ((T)1 + std::exp(-x)),
                            dy *y *((T)1 - y), true);
}
#endif
