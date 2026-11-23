#include <vector>
#include <iostream>
void relu(std::vector<float>& v) {
    std::cout << "[ReLU] Activating feature thresholds. Clipping negative noise..." << std::endl;
    for (int i =0; i < v.size(); ++i) {
        if (v[i] < 0) {
            v[i] = 0.0f;
        }
    }
};