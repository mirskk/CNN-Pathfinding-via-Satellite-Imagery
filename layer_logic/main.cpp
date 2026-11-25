#include "ImageProcessingInitial.h"
#include "maxPool1.h"
#include "convolution1.h"
#include "ReLU.h"
#include "maxPool3.h"
#include "maxPool4.h"
#include "maxPool5.h"
#include "maxPool6.h"
#include "maxPool7.h"
#include "maxPool8.h"
#include "convolution.h"
#include "FilterBank.h"
#include "Flattening.h"
#include "denseLayer.h"
#include <iostream>
#include <iomanip>
#include <random>
/*
g++ main.cpp convolution.cpp convolution1.cpp denseLayer.cpp Flattening.cpp ImageProcessingInitial.cpp maxPool1.cpp maxPool3.cpp maxPool4.cpp maxPool5.cpp maxPool6.cpp maxPool7.cpp maxPool8.cpp MSMT-A.cpp ReLU.cpp -o main.exe
*/

int main() {
    std::cout << "=== Starting Image Processing Debug Run ===" << std::endl;
    ImageProcessingInitial i;
    std::string imagePath = "C:\\Users\\name\\Desktop\\c++\\gps_imagery\\pics\\sc2.png";
    if (!i.preprocessImagePureCpp(imagePath)) {
        std::cerr << "Pipeline aborted due to image loading error." << std::endl;
        return -1;
    }

    std::cout << "Initializing ImageProcessingInitial via parameterized constructor..." << std::endl;
    int w = i.getW();
    int h = i.getH();
    if (w % 2 != 0 || h % 2 != 0) {
        std::cerr<<" Warning: Uneven resolutions will lead to unexpected data/results.";
        return -1;
    }
    std::cout << "Confirmed Image Specs: " << w << "x" << h << std::endl;
    std::cout << "Vector Size inside Main: " << i.getPixels().size() << std::endl;

    // 1st conv
    std::vector<float> layer1Data = loops_of_insanity(i);
    relu(layer1Data);
    
    int w1 = w - 2;
    int h1 = h - 2;

    // 1st pool
    std::vector<float> layer2Data = maxPoolLayer(layer1Data, w1, h1);
    int w2 = w1 / 2;
    int h2 = h1 / 2;

    Tensor l2tensor;
    l2tensor.data = layer2Data;
    l2tensor.w = w2;
    l2tensor.h  =h2;
    l2tensor.channels = 4;

    // 2nd conv
    Tensor layer3Data = runConvolution(l2tensor, 4, FilterBank::getLayer3Filters());
    relu(layer3Data.data);

    int w3 = layer3Data.w;
    int h3 = layer3Data.h;

    //2nd pool
    std::vector<float> layer6Data = maxPoolLayer6(layer3Data.data, w3, h3);
    int w6 = w3/ 2;
    int h6 = h3 / 2;

    Tensor l6;
    l6.data = layer6Data;
    l6.w = w6;
    l6.h = h6;
    l6.channels = 4;
    //3rd conv
    Tensor layer7Data = runConvolution(l6, 4, FilterBank::getLayer3Filters());
    relu(layer7Data.data);

    int w7 = layer7Data.w;
    int h7 = layer7Data.h;

    //3rd pool
    std::vector<float> layer8Data = maxPoolLayer8(layer7Data.data, w7, h7);

    int w8 = w7 / 2;
    int h8 = h7 / 2;

    Tensor l8;
    l8.data = layer8Data;
    l8.w = w8;
    l8.h = h8;
    l8.channels = 4;
    //4th conv
    Tensor layer9Data = runConvolution(l8, 8, FilterBank::getLayer3Filters());
    relu(layer9Data.data);

    int w9 = layer9Data.w;
    int h9 = layer9Data.h;
    //4th pool
    std::vector<float> layer10Data = maxPoolLayer10(layer9Data.data, w9, h9);

    int w10 = w9 / 2;
    int h10 = h9 / 2;

    Tensor l10;
    l10.data = layer10Data;
    l10.w = w10;
    l10.h = h10;
    l10.channels = 8;
    //5th conv
    Tensor layer11Data = runConvolution(l10, 16, FilterBank::getLayer4Filters());
    relu(layer11Data.data);

    int w11 = layer11Data.w;
    int h11 = layer11Data.h;
    //5th pool
    std::vector<float> layer12Data = maxPoolLayer12(layer11Data.data, w11, h11);
    
    int w12 = w11 / 2;
    int h12 = h11 / 2;

    Tensor l12;
    l12.data = layer12Data;
    l12.w = w12;
    l12.h = h12;
    l12.channels = 16;

    //6th conv
    //16-32
    Tensor layer13Data = runConvolution(l12, 32, FilterBank::getLayer5Filters());
    relu(layer13Data.data);

    int w13 = layer13Data.w;
    int h13 = layer13Data.h;
    //6th pool
    std::vector<float> layer14Data = maxPoolLayer14(layer13Data.data, w13, h13);

    int w14 = w13 / 2;
    int h14 = h13 / 2;

    Tensor l14;
    l14.data = layer14Data;
    l14.w = w14;
    l14.h = h14;
    l14.channels = 16;
    //7th conv
    Tensor layer15Data = runConvolution(l14, 32, FilterBank::getLayer5Filters());
    relu(layer15Data.data);

    int w15 = layer15Data.w;
    int h15 = layer15Data.h;
    //7th pool

    Tensor finalData;
    finalData.data = maxPoolLayer16(layer15Data.data, w15, h15);
    finalData.w = w15/2;
    finalData.h = h15/2;
    finalData.channels = 32;

    const Tensor finalPipeOut = flattenData(finalData);

    int inputsz = finalPipeOut.data.size();
    int units = 16;
    std::vector<float> bias(units, 0.0f);
    std::vector<std::vector<float>> kernel(inputsz, std::vector<float>(units));
    std::mt19937 gen(42);
    std::uniform_real_distribution<float> dist(-0.1f, 0.1f);
    for (int i = 0; i < inputsz; i++) {
        for (int j = 0; j < units; j++) {
            kernel[i][j] = dist(gen);
        }
    }
    // Tensor denseLayer(const Tensor& input, std::vector<std::vector<float>>& kernel, std::vector<float>& bias)
    Tensor denseLayer = denseLayer(&finalPipeOut, &kernel, &bias);
    std::cout<<" PIPELINE EXECUTED SUCCESSFULLY! " <<'\n';
    return 0;
}
