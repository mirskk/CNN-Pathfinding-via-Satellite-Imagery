#include <vector>
#include <iostream>
#include <algorithm>


std::vector<float> maxPoolLayer8(const std::vector<float>& layer7Input, int layer7Width, int layer7Height) {
    // --- DIAGNOSTIC START ---
    size_t expectedInputFloats = static_cast<size_t>(layer7Width) * layer7Height * 4;
    std::cout << "\n================ [MAXPOOL 4 DIAGNOSTIC START] ================" << std::endl;
    std::cout << "-> METADATA DIMENSIONS: W=" << layer7Width << ", H=" << layer7Height << ", C=4" << std::endl;
    std::cout << "-> ACTUAL VECTOR SIZE IN MEMORY: " << layer7Input.size() << " floats" << std::endl;
    if (layer7Input.size() != expectedInputFloats) {
        std::cout << "!! WARNING: Vector size does NOT match metadata dimensions! Mismatch = " 
                  << (static_cast<long long>(layer7Input.size()) - expectedInputFloats) << " floats." << std::endl;
    }
    // --- DIAGNOSTIC END ---

    std::vector<float> layer8output;
    int ps = 4;
    int rowStride = layer7Width * ps;

    int totalIterationsY = 0;
    int totalIterationsX = 0;

    // Running the exact loop bounding logic
    for (int j = 0; j + 1 < layer7Height; j += 2) {
        totalIterationsY++;
        totalIterationsX = 0; 
        for (int i = 0; i + 1 < layer7Width; i += 2) {
            totalIterationsX++;
            
            int topLeft = ((j * layer7Width) + i) * 4;
            int topRight = topLeft + ps;
            int bottomLeft = topLeft + rowStride;
            int bottomRight = topLeft + rowStride + ps;

            // Basic safety fence before accessing memory
            if (bottomRight + 3 >= layer7Input.size()) {
                std::cout << "!! CRITICAL: Loop tried to look out of bounds at vector index " << (bottomRight + 3) << std::endl;
                break;
            }

            for (int c = 0; c < 4; ++c) {
                float maxVal = std::max({
                    layer7Input[topLeft + c], 
                    layer7Input[topRight + c], 
                    layer7Input[bottomLeft + c], 
                    layer7Input[bottomRight + c]
                });
                layer8output.push_back(maxVal);
            }
        }
    }

    // --- DIAGNOSTIC SUMMARY ---
    std::cout << "-> LOOP SUMMARY: X-Axis ran " << totalIterationsX << " times. Y-Axis ran " << totalIterationsY << " times." << std::endl;
    std::cout << "-> TOTAL PIXELS POOLED: " << (totalIterationsX * totalIterationsY) << std::endl;
    std::cout << "-> EXPECTED OUTPUT FLOATS: " << (totalIterationsX * totalIterationsY * 4) << std::endl;
    std::cout << "-> ACTUAL OUTPUT FLOATS GENERATED: " << layer8output.size() << std::endl;
    std::cout << "================= [MAXPOOL 4 DIAGNOSTIC END] =================\n" << std::endl;

    return layer8output;
}
