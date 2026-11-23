#include <vector>
#include <iostream>
#include <algorithm>

std::vector<float> maxPoolLayer14(const std::vector<float>& layer13Input, int layer13Width, int layer13Height) {
    // --- DIAGNOSTIC START ---
    size_t expectedInputFloats = static_cast<size_t>(layer13Width) * layer13Height * 16;
    std::cout << "\n================ [MAXPOOL 7 DIAGNOSTIC START] ================" << std::endl;
    std::cout << "-> METADATA DIMENSIONS: W=" << layer13Width << ", H=" << layer13Height << std::endl;
    std::cout << "-> ACTUAL VECTOR SIZE IN MEMORY: " << layer13Input.size() << " floats" << std::endl;
    if (layer13Input.size() != expectedInputFloats) {
        std::cout << "!! WARNING: Vector size does NOT match metadata dimensions! Mismatch = " 
                  << (static_cast<long long>(layer13Input.size()) - expectedInputFloats) << " floats." << std::endl;
    }
    // --- DIAGNOSTIC END ---

    std::vector<float> layer14output;
    int ps = 16;
    int rowStride = layer13Width * ps;

    int totalIterationsY = 0;
    int totalIterationsX = 0;

    // Running the exact loop bounding logic
    for (int j = 0; j < layer13Height - 1; j += 2) {
        totalIterationsY++;
        totalIterationsX = 0; 
        for (int i = 0; i < layer13Width - 1; i += 2) {
            totalIterationsX++;
            
            int topLeft = ((j * layer13Width) + i) * 32;
            int topRight = topLeft + ps;
            int bottomLeft = topLeft + rowStride;
            int bottomRight = topLeft + rowStride + ps;

            // Basic safety fence before accessing memory
            if (bottomRight + 3 >= layer13Input.size()) {
                std::cout << "!! CRITICAL: Loop tried to look out of bounds at vector index " << (bottomRight + 3) << std::endl;
                break;
            }

            for (int c = 0; c < 32; ++c) {
                float maxVal = std::max({
                    layer13Input[topLeft + c], 
                    layer13Input[topRight + c], 
                    layer13Input[bottomLeft + c], 
                    layer13Input[bottomRight + c]
                });
                layer14output.push_back(maxVal);
            }
        }
    }

    // --- DIAGNOSTIC SUMMARY ---
    std::cout << "-> LOOP SUMMARY: X-Axis ran " << totalIterationsX << " times. Y-Axis ran " << totalIterationsY << " times." << std::endl;
    std::cout << "-> TOTAL PIXELS POOLED: " << (totalIterationsX * totalIterationsY) << std::endl;
    std::cout << "-> EXPECTED OUTPUT FLOATS: " << (totalIterationsX * totalIterationsY * 32) << std::endl;
    std::cout << "-> ACTUAL OUTPUT FLOATS GENERATED: " << layer14output.size() << std::endl;
    std::cout << "================= [MAXPOOL 7 DIAGNOSTIC END] =================\n" << std::endl;

    return layer14output;
}