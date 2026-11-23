#include <vector>
#include <iostream>
#include <algorithm>

std::vector<float> maxPoolLayer12(const std::vector<float>& layer11Input, int layer11Width, int layer11Height) {
    // --- DIAGNOSTIC START ---
    size_t expectedInputFloats = static_cast<size_t>(layer11Width) * layer11Height * 16;
    std::cout << "\n================ [MAXPOOL 6 DIAGNOSTIC START] ================" << std::endl;
    std::cout << "-> METADATA DIMENSIONS: W=" << layer11Width << ", H=" << layer11Height << std::endl;
    std::cout << "-> ACTUAL VECTOR SIZE IN MEMORY: " << layer11Input.size() << " floats" << std::endl;
    if (layer11Input.size() != expectedInputFloats) {
        std::cout << "!! WARNING: Vector size does NOT match metadata dimensions! Mismatch = " 
                  << (static_cast<long long>(layer11Input.size()) - expectedInputFloats) << " floats." << std::endl;
    }
    // --- DIAGNOSTIC END ---

    std::vector<float> layer12output;
    int ps = 16;
    int rowStride = layer11Width * ps;

    int totalIterationsY = 0;
    int totalIterationsX = 0;

    // Running the exact loop bounding logic
    for (int j = 0; j < layer11Height - 1; j += 2) {
        totalIterationsY++;
        totalIterationsX = 0; 
        for (int i = 0; i < layer11Width - 1; i += 2) {
            totalIterationsX++;
            
            int topLeft = ((j * layer11Width) + i) * 16;
            int topRight = topLeft + ps;
            int bottomLeft = topLeft + rowStride;
            int bottomRight = topLeft + rowStride + ps;

            // Basic safety fence before accessing memory
            if (bottomRight + 3 >= layer11Input.size()) {
                std::cout << "!! CRITICAL: Loop tried to look out of bounds at vector index " << (bottomRight + 3) << std::endl;
                break;
            }

            for (int c = 0; c < 16; ++c) {
                float maxVal = std::max({
                    layer11Input[topLeft + c], 
                    layer11Input[topRight + c], 
                    layer11Input[bottomLeft + c], 
                    layer11Input[bottomRight + c]
                });
                layer12output.push_back(maxVal);
            }
        }
    }

    // --- DIAGNOSTIC SUMMARY ---
    std::cout << "-> LOOP SUMMARY: X-Axis ran " << totalIterationsX << " times. Y-Axis ran " << totalIterationsY << " times." << std::endl;
    std::cout << "-> TOTAL PIXELS POOLED: " << (totalIterationsX * totalIterationsY) << std::endl;
    std::cout << "-> EXPECTED OUTPUT FLOATS: " << (totalIterationsX * totalIterationsY * 16) << std::endl;
    std::cout << "-> ACTUAL OUTPUT FLOATS GENERATED: " << layer12output.size() << std::endl;
    std::cout << "================= [MAXPOOL 6 DIAGNOSTIC END] =================\n" << std::endl;

    return layer12output;
}