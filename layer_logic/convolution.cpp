#include <vector>
#include "Tensor.h"
#include <iostream>
Tensor runConvolution(
    const Tensor& input,
    int numOutputChannels,
    const std::vector<std::vector<std::vector<std::vector<float>>>>& filters
) {
    int currentWidth = input.w;
    int currentHeight = input.h;
    int numInputChannels = input.channels;

    int ps = numInputChannels;
    int rowStride = currentWidth * ps;

    Tensor layeroutput;
    layeroutput.w = currentWidth - 2;
    layeroutput.h = currentHeight - 2;
    layeroutput.channels = numOutputChannels;
    layeroutput.data.reserve(layeroutput.w * layeroutput.h * layeroutput.channels);
    
    float totalPxSum;
    std::cout<<"Reporting grid size before modifications. W: "<<currentWidth<<", H: "<<currentHeight<<", Ch: "<<layeroutput.channels<<std::endl;
    for (int j = 1; j < currentHeight - 1; j++) {
        for (int i = 1; i < currentWidth - 1; i++ ) {
            int i5center = ((j * currentWidth) + i ) * ps;
            int i1 = i5center - rowStride - ps;
            int i2 = i5center - rowStride;
            int i3 = i5center - rowStride + ps;
            int i4 = i5center - ps;
            int i6 = i5center + ps;
            int i7 = i5center + rowStride - ps;
            int i8 = i5center + rowStride;
            int i9 = i5center + rowStride + ps;

            int ns[9] = { i1, i2, i3, i4, i5center, i6, i7, i8, i9 };

            for (int f = 0; f < numOutputChannels; ++f) {
                totalPxSum = 0.0f;

                for (int n=0; n < 9; ++n) {
                    int row = n / 3;
                    int col = n % 3;

                    for (int c = 0; c < numInputChannels; ++c) {
                        totalPxSum += input.data[ns[n] + c] * filters[f][row][col][c];
                    }
                }
                layeroutput.data.push_back(totalPxSum);
            }

        }
    }
    std::cout << "[Conv] Scan complete. Output grid size: " 
          << (currentWidth - 2) << "x" << (currentHeight - 2) 
          << " with "<<layeroutput.channels<<" channels (" << layeroutput.data.size() << " total floats)." << std::endl;
    return layeroutput;
}