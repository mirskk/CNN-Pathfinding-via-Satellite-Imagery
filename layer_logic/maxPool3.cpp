#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
//max pooling v2

std::vector<float> maxPoolLayer6(const std::vector<float>& layer5Input, int layer5Width, int layer5Height) {
    std::vector<float> layer6output;
    int ps = 4;
    int rowStride = layer5Width * ps;
    std::cout << "[MaxPool 3] Starting 2x2 tournament stride (Pool Factor: 2x)..." << std::endl;
    for (int j = 0; j + 1 < layer5Height; j += 2) {
        for (int i = 0; i + 1 < layer5Width; i += 2) {
            int topLeft = ((j * layer5Width) + i) * 4;
            int topRight = topLeft + ps;
            int bottomLeft = topLeft + rowStride;
            int bottomRight = topLeft + rowStride + ps;

            float a1 = layer5Input[topLeft];
            float a2 = layer5Input[topRight];
            float a3 = layer5Input[bottomLeft];
            float a4 = layer5Input[bottomRight];

            float maxA = std::max({a1, a2, a3, a4});

            float b1 = layer5Input[topLeft + 1];
            float b2 = layer5Input[topRight + 1];
            float b3 = layer5Input[bottomLeft + 1];
            float b4 = layer5Input[bottomRight + 1];

            float maxB = std::max({b1, b2, b3, b4});

            float c1 = layer5Input[topLeft + 2];
            float c2 = layer5Input[topRight + 2];
            float c3 = layer5Input[bottomLeft + 2];
            float c4 = layer5Input[bottomRight + 2];

            float maxC = std::max({c1, c2, c3, c4});

            float d1 = layer5Input[topLeft + 3];
            float d2 = layer5Input[topRight + 3];
            float d3 = layer5Input[bottomLeft + 3];
            float d4 = layer5Input[bottomRight + 3];

            float maxD = std::max({d1, d2, d3, d4});

            layer6output.push_back(maxA);
            layer6output.push_back(maxB);
            layer6output.push_back(maxC);
            layer6output.push_back(maxD);
        }
    }
    std::cout << "[MaxPool 3] Compression complete! Shrunk grid size to: " 
          << std::floor(layer5Width / 2) << "x" << std::floor(layer5Height / 2) 
          << " (" << layer6output.size() << " total floats)." << std::endl;
    return layer6output;
};