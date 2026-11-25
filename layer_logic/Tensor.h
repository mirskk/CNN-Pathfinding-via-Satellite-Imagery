#pragma once
#include <vector>

struct Tensor {
    std::vector<float> data;
    int w = 0;
    int h = 0;
    int channels = 0;

    // default constructor
    Tensor() = default;
    
    // parameterized constructor
    Tensor(int width, int height, int ch) 
        : w(width), h(height), channels(ch) {
        data.reserve(w * h * channels);
    }
};
