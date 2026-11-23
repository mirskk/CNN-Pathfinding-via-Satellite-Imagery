#pragma once
#include <vector>
#include "Tensor.h"
Tensor runConvolution(
    const Tensor& inputInput,
    int numOutputChannels,
    const std::vector<std::vector<std::vector<std::vector<float>>>>& filters
);