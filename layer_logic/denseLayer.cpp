#include <iostream>
#include <vector>
//#include <ReLU.h> - no activation here, activation in main
#include "Tensor.h"

Tensor denseLayer(const Tensor& input, std::vector<std::vector<float>>& kernel, std::vector<float>& bias) {
    int inputsz = input.data.size();
    int units = bias.size();
    Tensor layeroutput(1, 1, units);

    for (int u = 0; u < units; u++) {
        float sum = bias[u];
        for (int i = 0; i < inputsz; i++) {
            sum += input.data[i] * kernel[i][u];
        }
        layeroutput.data.push_back(sum);
    }
    std::cout<<"[ Dense Layer Job Finished ]:  There is now a tensor object with: \n
    - "<<layeroutput.h<<" height;\n
    - "<<layeroutput.w<<" width;\n
    - with a "<<layeroutput.data.size()<<" size;"<<std::endl;
    return layeroutput;

};