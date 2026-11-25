#include "ImageProcessingInitial.h"
#include <vector>
#include "ReLU.h"
#include <iostream>
static const float boxV[3][3] = {
    {-1.0f, 2.0f, -1.0f},
    {-1.0f, 2.0f, -1.0f},
    {-1.0f, 2.0f, -1.0f}
};

static const float boxH[3][3] = {
    {-1.0f, -1.0f, -1.0f},
    {2.0f, 2.0f, 2.0f},
    {-1.0f, -1.0f, -1.0f}
};

static const float boxRD[3][3] = {
    {2.0f, -1.0f, -1.0f},
    {-1.0f, 2.0f, -1.0f},
    {-1.0f, -1.0f, 2.0f}
};

static const float boxLD[3][3] = {
    {-1.0f, -1.0f, 2.0f},
    {-1.0f, 2.0f, -1.0f},
    {2.0f, -1.0f, -1.0f}
};

std::vector<float> loops_of_insanity(const ImageProcessingInitial& img) { //possibly pass the function a reference for a temp object
    int ps = 3;
    int rowStride = img.getW() * 3; //one full row of floats
    std::cout<< rowStride << " : ROWSTRIDE"<<std::endl;
    std::vector<float> layer1output;

    std::cout << "DEBUG -> getW(): " << img.getW() << ", getH(): " << img.getH() << std::endl;
    long long calculated_size = (static_cast<long long>(img.getW()) - 2) * (static_cast<long long>(img.getH()) - 2) * 4;
    std::cout << "DEBUG -> Target Reserve Size: " << calculated_size << std::endl;

    layer1output.reserve((img.getW() - 2) * (img.getH() - 2) * 4);
    std::cout<< "Reserved size for layer 1 output: " << ((img.getW() - 2) * (img.getH() - 2) * 4)<<std::endl;
    std::cout<< "Vector MAX index: " << img.getPixels().size() - 1 <<std::endl;
    std::cout << "[Layer 1: Conv2D] Starting unpadded drone sweep using 4 filters..." << std::endl;
    for (int j = 1; j < img.getH() - 1; j++) {
        for (int i = 1; i < img.getW() - 1; i++) {
            int i5center = ((j * img.getW()) + i ) * 3;
            int i1 = i5center - rowStride - ps;
            int i2 = i5center - rowStride;
            int i3 = i5center - rowStride + ps;
            int i4 = i5center - ps;
            int i6 = i5center + ps;
            int i7 = i5center + rowStride - ps;
            int i8 = i5center + rowStride;
            int i9 = i5center + rowStride + ps;

            long long max_index = img.getPixels().size();

            if (i1 < 0 || i9 >= max_index) {    
                std::cout << "\n[!] CRASH PREVENTED at row j = " << j << ", col i = " << i << std::endl;
                std::cout << "Vector Max Allowed Index: " << max_index - 1 << std::endl;
                std::cout << "Calculated i1 (lowest): " << i1 << std::endl;
                std::cout << "Calculated i5center:    " << i5center << std::endl;
                std::cout << "Calculated i9 (highest): " << i9 << std::endl;
                std::cout << "Skipping this iteration to prevent out-of-bounds access." << std::endl;
                return layer1output; 
            }

            float p1 = img.getPixels()[i1];
            float p2 = img.getPixels()[i2];
            float p3 = img.getPixels()[i3];
            float p4 = img.getPixels()[i4];
            float p5 = img.getPixels()[i5center];
            float p6 = img.getPixels()[i6];
            float p7 = img.getPixels()[i7];
            float p8 = img.getPixels()[i8];
            float p9 = img.getPixels()[i9];

            float resV = (p1 * boxV[0][0]) + (p2 * boxV[0][1]) + (p3 * boxV[0][2]) + (p4 * boxV[1][0]) + (p5 * boxV[1][1]) + (p6 * boxV[1][2]) + (p7 * boxV[2][0]) + (p8 * boxV[2][1]) + (p9 * boxV[2][2]);
            float resH = (p1 * boxH[0][0]) + (p2 * boxH[0][1]) + (p3 * boxH[0][2]) + (p4 * boxH[1][0]) + (p5 * boxH[1][1]) + (p6 * boxH[1][2]) + (p7 * boxH[2][0]) + (p8 * boxH[2][1]) + (p9 * boxH[2][2]);
            float resRD = (p1 * boxRD[0][0]) + (p2 * boxRD[0][1]) + (p3 * boxRD[0][2]) + (p4 * boxRD[1][0]) + (p5 * boxRD[1][1]) + (p6 * boxRD[1][2]) + (p7 * boxRD[2][0]) + (p8 * boxRD[2][1]) + (p9 * boxRD[2][2]);
            float resLD = (p1 * boxLD[0][0]) + (p2 * boxLD[0][1]) + (p3 * boxLD[0][2]) + (p4 * boxLD[1][0]) + (p5 * boxLD[1][1]) + (p6 * boxLD[1][2]) + (p7 * boxLD[2][0]) + (p8 * boxLD[2][1]) + (p9 * boxLD[2][2]);
            layer1output.push_back(resV);
            layer1output.push_back(resH);
            layer1output.push_back(resRD);
            layer1output.push_back(resLD);
        }
    }
    relu(layer1output);
    std::cout << "[Layer 1: Conv2D] Scan complete. Output grid size: " 
          << (img.getW() - 2) << "x" << (img.getH() - 2) 
          << " with 4 channels (" << layer1output.size() << " total floats)." << std::endl;
    return layer1output;
}

// int main() {
//     std::cout << "=== Starting Image Processing Debug Run ===" << std::endl;
//     int mockWidth = 1282;
//     int mockHeight = 720;
//     std::vector<float> mockPixels(mockWidth * mockHeight * 3, 1.0f); 
//     std::cout << "Initializing mock image data..." << std::endl;
//     ImageProcessingInitial mockImg(mockWidth, mockHeight, mockPixels);
//     std::cout<< mockImg.getW() << " x " << mockImg.getH()<<std::endl;
//     std::cout << "Executing loops_of_insanity..." << std::endl;
//     std::vector<float> output = loops_of_insanity(mockImg);
//     std::cout << "\n=== Execution Analysis ===" << std::endl;
//     std::cout << "Output vector size: " << output.size() << std::endl;
//     if (!output.empty()) {
//         std::cout << "First 8 results: ";
//         for (size_t i = 0; i < std::min(output.size(), size_t(8)); ++i) {
//             std::cout << output[i] << " ";
//         }
//         std::cout << std::endl;
//     }
//     std::cout << "=== Debug Run Finished ===" << std::endl;
//     return 0;
// }
