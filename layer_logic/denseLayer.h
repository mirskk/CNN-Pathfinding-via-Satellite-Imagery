#pragma once
#include <DenseLayer1.cpp>

Tensor DenseLayer(const Tensor& input, std::vector<std::vector<float>>& kernel, std::vector<float>& bias);

#endif