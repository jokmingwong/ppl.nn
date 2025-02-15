// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include "ppl/nn/engines/cuda/optimizer/algos/algo_filter_manager.h"

using namespace ppl::common;

namespace ppl { namespace nn { namespace cuda {

const AlgoFilter* AlgoFilterManager::FindKernel(const std::string& type) const {
    auto ref = type2algo_.find(type);
    if (ref == type2algo_.end()) {
        return nullptr;
    }
    return &ref->second;
}

#define REGISTER_ALGO_FILTER_INFO(impl, classname) \
    do {                                           \
        type2algo_[impl].AppendAlgo(&classname);   \
    } while (0)

template <typename T>
void AlgoFilterManager::Register(const std::string& kernel_type, T& algo_type) {
    REGISTER_ALGO_FILTER_INFO(kernel_type, algo_type);
}

AlgoFilterManager::AlgoFilterManager() {
    REGISTER_ALGO_FILTER_INFO("Conv", turing_hmma_imp_);
    REGISTER_ALGO_FILTER_INFO("Conv", turing_imma_imp_);
    REGISTER_ALGO_FILTER_INFO("Conv", depthwise_direct_imp_);
    REGISTER_ALGO_FILTER_INFO("Conv", depthwise_direct_imp_int8_);
    REGISTER_ALGO_FILTER_INFO("ConvTranspose", convtranspose_imp_);
    REGISTER_ALGO_FILTER_INFO("Bridge", bridge_imp_);
    REGISTER_ALGO_FILTER_INFO("Concat", concat_imp_);
    REGISTER_ALGO_FILTER_INFO("Gemm", gemm_imp_);
    REGISTER_ALGO_FILTER_INFO("LSTM", lstm_imp_);
    REGISTER_ALGO_FILTER_INFO("PRelu", prelu_imp_);
    REGISTER_ALGO_FILTER_INFO("MMCVModulatedDeformConv2d", deform_conv_imp_);
    REGISTER_ALGO_FILTER_INFO("MatMul", matmul_imp_);
    REGISTER_ALGO_FILTER_INFO("Normal", normal_imp_);
}

}}} // namespace ppl::nn::cuda
