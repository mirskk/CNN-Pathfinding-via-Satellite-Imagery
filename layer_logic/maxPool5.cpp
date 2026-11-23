#include <vector>
#include <iostream>
#include <algorithm>

std::vector<float> maxPoolLayer10(const std::vector<float>& layer9Input, int layer9Width, int layer9Height) {
    // --- DIAGNOSTIC START ---
    size_t expectedInputFloats = static_cast<size_t>(layer9Width) * layer9Height * 8;
    std::cout << "\n================ [MAXPOOL 5 DIAGNOSTIC START] ================" << std::endl;
    std::cout << "-> METADATA DIMENSIONS: W=" << layer9Width << ", H=" << layer9Height << std::endl;
    std::cout << "-> ACTUAL VECTOR SIZE IN MEMORY: " << layer9Input.size() << " floats" << std::endl;
    if (layer9Input.size() != expectedInputFloats) {
        std::cout << "!! WARNING: Vector size does NOT match metadata dimensions! Mismatch = " 
                  << (static_cast<long long>(layer9Input.size()) - expectedInputFloats) << " floats." << std::endl;
    }
    // --- DIAGNOSTIC END ---

    std::vector<float> layer10output;
    int ps = 8;
    int rowStride = layer9Width * ps;

    int totalIterationsY = 0;
    int totalIterationsX = 0;

    // Running the exact loop bounding logic
    for (int j = 0; j < layer9Height - 1; j += 2) {
        totalIterationsY++;
        totalIterationsX = 0; 
        for (int i = 0; i < layer9Width - 1; i += 2) {
            totalIterationsX++;
            
            int topLeft = ((j * layer9Width) + i) * 8;
            int topRight = topLeft + ps;
            int bottomLeft = topLeft + rowStride;
            int bottomRight = topLeft + rowStride + ps;

            // Basic safety fence before accessing memory
            if (bottomRight + 3 >= layer9Input.size()) {
                std::cout << "!! CRITICAL: Loop tried to look out of bounds at vector index " << (bottomRight + 3) << std::endl;
                break;
            }

            for (int c = 0; c < 8; ++c) {
                float maxVal = std::max({
                    layer9Input[topLeft + c], 
                    layer9Input[topRight + c], 
                    layer9Input[bottomLeft + c], 
                    layer9Input[bottomRight + c]
                });
                layer10output.push_back(maxVal);
            }
        }
    }

    // --- DIAGNOSTIC SUMMARY ---
    std::cout << "-> LOOP SUMMARY: X-Axis ran " << totalIterationsX << " times. Y-Axis ran " << totalIterationsY << " times." << std::endl;
    std::cout << "-> TOTAL PIXELS POOLED: " << (totalIterationsX * totalIterationsY) << std::endl;
    std::cout << "-> EXPECTED OUTPUT FLOATS: " << (totalIterationsX * totalIterationsY * 8) << std::endl;
    std::cout << "-> ACTUAL OUTPUT FLOATS GENERATED: " << layer10output.size() << std::endl;
    std::cout << "================= [MAXPOOL 5 DIAGNOSTIC END] =================\n" << std::endl;

    return layer10output;
}