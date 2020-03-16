#pragma once

#include <torch/csrc/jit/ir/ir.h>

/*
 * This file contains APIs for cuda fuser;
 *
 * We use an empty static struct to hold the function pointers, which are
 * registered separately. This is to support cpu-only compilation.
 * Registration is done in torch/csrc/jit/codegen/cuda/register_interface.cpp
 */

namespace torch {
namespace jit {
namespace fuser {
namespace cuda {

// dummy struct to allow API registration
struct CudaFuserInterface {
  bool (*fn_is_fusible_n_)(const Node* const) = nullptr;
  bool (*fn_is_fusible_n_n_)(const Node* const, const Node* const) = nullptr;
  void (*fn_compile_n_)(Node*) = nullptr;
  void (*fn_run_n_s_)(const Node* const, Stack&) = nullptr;
};

// Get interface, this is used by registration and user facing API internally
TORCH_API CudaFuserInterface* getFuserInterface();

// Customer facing APIs vvv

// Query if node is fusable for cuda codegen
TORCH_API bool isFusable(const Node* const node);
TORCH_API bool isFusable(const Node* const fusion, const Node* const node);

// redirect to compileCudaFusionGroup (manager.h)
TORCH_API void compileFusionGroup(Node* fusion_node);
// redirect to runCudaFusionGroup (manager.h)
TORCH_API void runFusionGroup(const Node* const fusion_node, Stack& stack);

}}}} // namespace torch::jit::fuser::cuda
