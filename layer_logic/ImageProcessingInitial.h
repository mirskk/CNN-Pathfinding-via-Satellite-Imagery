#pragma once
#ifndef IMAGEPROCESSINGINITIAL_H
#define IMAGEPROCESSINGINITIAL_H
#include <vector>
#include <string>

class ImageProcessingInitial {
protected:
    int width, height, channels;
    std::vector<float> normalizedPixels;
public:
    ImageProcessingInitial();
    ImageProcessingInitial(int w, int h, std::vector<float> mp);
    int getW() const;
    int getH() const;
    int getChannels() const;
    const std::vector<float>& getPixels() const;
    bool preprocessImagePureCpp(const std::string& imagePath);
    ~ImageProcessingInitial();
};
#endif