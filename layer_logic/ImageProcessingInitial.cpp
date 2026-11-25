#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <vector>
#include <string>
#include "ImageProcessingInitial.h"

ImageProcessingInitial::ImageProcessingInitial() {
    //
}

ImageProcessingInitial::ImageProcessingInitial(int w, int h, std::vector<float> mp) : width(w), height(h), channels(3), normalizedPixels(mp){
    //
}

int ImageProcessingInitial::getW() const { return width; }

int ImageProcessingInitial::getH() const { return height; }

int ImageProcessingInitial::getChannels() const { return channels; }

const std::vector<float>& ImageProcessingInitial::getPixels() const { return normalizedPixels; }

ImageProcessingInitial::~ImageProcessingInitial() { 
    //
}

bool ImageProcessingInitial::preprocessImagePureCpp(const std::string &imagePath) {
    unsigned char* rawPixels = stbi_load(imagePath.c_str(), &width, &height, &channels, 3);
    if (rawPixels == nullptr) {
        std::cerr << "Error: Could not open or find the image via STB!" << std::endl;
        return false;
    }
    std::cout << "Successfully loaded satellite tile image!" << std::endl;
    std::cout << "Dimensions: " << getW() << "x" << getH() << std::endl;
    int totalFloats = getW() * getH() * 3;
    // std::vector<float> normalizedPixels(totalFloats);

    /*Char is still an integer in a way if you think about it, so, we sort of turn those 
    integers into floats so that we can divide by the 255.0f? 
    And the .0f part is there to prevent integer division?*/
    normalizedPixels.resize(totalFloats);
    
    for (int i = 0; i < totalFloats; ++i) {
        normalizedPixels[i] = static_cast<float>(rawPixels[i]) / 255.0f;
    }

    std::cout << "Normalized Pixel (0,0) -> R: " << normalizedPixels[0] 
              << ", G: " << normalizedPixels[1] 
              << ", B: " << normalizedPixels[2] << std::endl;

    stbi_image_free(rawPixels);
    return true;
}

// int main() {
//     std::string testPath = "C:\\Users\\name\\Desktop\\c++\\gps_imagery\\pics\\sc1.png"; // PATH
//     ImageProcessingInitial p;
//     p.preprocessImagePureCpp(testPath);
//     std::cout << "\nPress ENTER to close this window..." << std::endl;
//     std::cin.get();
//     return 0;
// }

