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

#ifndef _ST_HPC_PPL_NN_ENGINES_CUDA_OPTIMIZER_OPS_PMX_SHAPE_OP_H_
#define _ST_HPC_PPL_NN_ENGINES_CUDA_OPTIMIZER_OPS_PMX_SHAPE_OP_H_

#include "ppl/nn/engines/cuda/optimizer/opt_kernel.h"

#include "ppl/nn/engines/common/pmx/shape_operation_op.h"

namespace ppl { namespace nn { namespace cuda {

class PPLShapeOperationOp final : public CudaOptKernel {
public:
    PPLShapeOperationOp(const ir::Node* node) : CudaOptKernel(node), op_(node) {}
    KernelImpl* CreateKernelImpl() const override;
    ppl::common::RetCode Init(const OptKernelOptions&) override;
    ppl::common::RetCode Finalize(const OptKernelOptions& options) override;
#ifdef PPLNN_ENABLE_PMX_MODEL
    ppl::common::RetCode SerializeData(const pmx::SerializationContext&, utils::DataStream*) const override {
        return ppl::common::RC_UNSUPPORTED;
    };
    ppl::common::RetCode DeserializeData(const pmx::DeserializationContext&, const void*, uint64_t) override {
        return ppl::common::RC_UNSUPPORTED;
    };
#endif

    void* GetParam() override {
        return (void*)&param_;
    };

private:
    ppl::nn::pmx::ShapeOperationParam param_;
    ppl::nn::pmx::ShapeOperationOp op_;
};

}}} // namespace ppl::nn::cuda

#endif
