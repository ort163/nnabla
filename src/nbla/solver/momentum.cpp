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

#include <algorithm>
#include <nbla/solver/momentum.hpp>

namespace nbla {
using std::shared_ptr;
using std::make_shared;

NBLA_REGISTER_SOLVER_SOURCE(Momentum, float, float);

template <typename T>
Momentum<T>::Momentum(const Context &ctx, float lr, float momentum)
    : BaseSolver<T>(ctx), lr_(lr), momentum_(momentum) {}

template <typename T> Momentum<T>::~Momentum() {}

template <typename T>
void Momentum<T>::set_state_impl(const string &key, VariablePtr param) {
  auto shape = param->shape();
  auto m = make_shared<Variable>(shape);
  m->data()->zero();
  state_.insert({key, m});
}
template <typename T> void Momentum<T>::remove_state_impl(const string &key) {
  state_.erase(key);
}

template <typename T>
void Momentum<T>::update_impl(const string &key, VariablePtr param) {
  Size_t size = param->size();
  VariablePtr v_ = state_.at(key);
  T *v = v_->cast_data_and_get_pointer<T>(this->ctx_);
  const T *grad = param->get_grad_pointer<T>(this->ctx_);
  T *data = param->cast_data_and_get_pointer<T>(this->ctx_);
  std::transform(grad, grad + size, v, v,
                 [this](T g, T v) { return momentum_ * v + lr_ * g; });
  std::transform(v, v + size, data, data, [this](T v, T x) { return x - v; });
}

// Template instanciation
template class Momentum<float>;
}
