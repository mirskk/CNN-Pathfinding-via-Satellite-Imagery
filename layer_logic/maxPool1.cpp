//max pooling
#include <vector>
#include <algorithm>
#include <cmath>
#include "maxPool1.h"
#include <iostream>

// V, H, RD, LD
std::vector<float> maxPoolLayer(const std::vector<float>& layer1Input, int layer1Width, int layer1Height) {
    std::vector<float> layer2output;
    int ps = 4;
    int rowStride = layer1Width * ps;
    std::cout << "[MaxPool 1] Starting 2x2 tournament stride (Pool Factor: 2x)..." << std::endl;
    for (int j = 0; j < layer1Height - 1; j += 2) {
        for (int i = 0; i < layer1Width - 1; i+= 2 ) {

            int topLeft = ((j * layer1Width) + i) * 4;
            int topRight = topLeft + ps;
            int bottomLeft = topLeft + rowStride;
            int bottomRight = topLeft + rowStride + ps;

            float v1 = layer1Input[topLeft];
            float v2 = layer1Input[topRight];
            float v3 = layer1Input[bottomLeft];
            float v4 = layer1Input[bottomRight];

            float maxV = std::max({v1, v2, v3, v4});

            float h1 = layer1Input[topLeft + 1];
            float h2 = layer1Input[topRight + 1];
            float h3 = layer1Input[bottomLeft + 1];
            float h4 = layer1Input[bottomRight + 1];

            float maxH = std::max({h1, h2, h3, h4});

            float rd1 = layer1Input[topLeft + 2];
            float rd2 = layer1Input[topRight + 2];
            float rd3 = layer1Input[bottomLeft + 2];
            float rd4 = layer1Input[bottomRight + 2];

            float maxRD = std::max({rd1, rd2, rd3, rd4});

            float ld1 = layer1Input[topLeft + 3];
            float ld2 = layer1Input[topRight + 3];
            float ld3 = layer1Input[bottomLeft + 3];
            float ld4 = layer1Input[bottomRight + 3];

            float maxLD = std::max({ld1, ld2, ld3, ld4});

            layer2output.push_back(maxV);
            layer2output.push_back(maxH);
            layer2output.push_back(maxRD);
            layer2output.push_back(maxLD);
        }
    }
    std::cout << "[MaxPool 1] Compression complete! Shrunk grid size to: " 
          << std::floor(layer1Width / 2) << "x" << std::floor(layer1Height / 2) 
          << " (" << layer2output.size() << " total floats)." << std::endl;
          //layer 2 outputs 4 channels
    return layer2output;
};
