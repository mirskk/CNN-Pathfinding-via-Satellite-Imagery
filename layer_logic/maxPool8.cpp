#include <vector>
#include <iostream>
#include <algorithm>

std::vector<float> maxPoolLayer16(const std::vector<float>& layer15Input, int layer15Width, int layer15Height) {
    // --- DIAGNOSTIC START ---
    size_t expectedInputFloats = static_cast<size_t>(layer15Width) * layer15Height * 32;
    std::cout << "\n================ [MAXPOOL 8 DIAGNOSTIC START] ================" << std::endl;
    std::cout << "-> METADATA DIMENSIONS: W=" << layer15Width << ", H=" << layer15Height << std::endl;
    std::cout << "-> ACTUAL VECTOR SIZE IN MEMORY: " << layer15Input.size() << " floats" << std::endl;
    if (layer15Input.size() != expectedInputFloats) {
        std::cout << "!! WARNING: Vector size does NOT match metadata dimensions! Mismatch = " 
                  << (static_cast<long long>(layer15Input.size()) - expectedInputFloats) << " floats." << std::endl;
    }
    // --- DIAGNOSTIC END ---

    std::vector<float> layer16output;
    int ps = 32;
    int rowStride = layer15Width * ps;

    int totalIterationsY = 0;
    int totalIterationsX = 0;

    // Running the exact loop bounding logic
    for (int j = 0; j + 1 < layer15Height; j += 2) {
        totalIterationsY++;
        totalIterationsX = 0; 
        for (int i = 0; i + 1 < layer15Width; i += 2) {
            totalIterationsX++;
            
            int topLeft = ((j * layer15Width) + i) * ps;
            int topRight = topLeft + ps;
            int bottomLeft = topLeft + rowStride;
            int bottomRight = topLeft + rowStride + ps;

            // Basic safety fence before accessing memory
            if (bottomRight + 3 >= layer15Input.size()) {
                std::cout << "!! CRITICAL: Loop tried to look out of bounds at vector index " << (bottomRight + 3) << std::endl;
                break;
            }

            for (int c = 0; c < 32; ++c) {
                float maxVal = std::max({
                    layer15Input[topLeft + c], 
                    layer15Input[topRight + c], 
                    layer15Input[bottomLeft + c], 
                    layer15Input[bottomRight + c]
                });
                layer16output.push_back(maxVal);
            }
        }
    }

    // --- DIAGNOSTIC SUMMARY ---
    std::cout << "-> LOOP SUMMARY: X-Axis ran " << totalIterationsX << " times. Y-Axis ran " << totalIterationsY << " times." << std::endl;
    std::cout << "-> TOTAL PIXELS POOLED: " << (totalIterationsX * totalIterationsY) << std::endl;
    std::cout << "-> EXPECTED OUTPUT FLOATS: " << (totalIterationsX * totalIterationsY * 64) << std::endl;
    std::cout << "-> ACTUAL OUTPUT FLOATS GENERATED: " << layer16output.size() << std::endl;
    std::cout << "-> Size: W: " <<layer15Width/2<<", H: "<<layer15Height/2<<", Channels: "<<32<< std::endl;
    std::cout << "================= [MAXPOOL 8 DIAGNOSTIC END] =================\n" << std::endl;

    return layer16output;
}