#include <iostream>
#include "MSMT-A.h"

int main() {
    int W = 4, H = 4;
    // 4x4 probability grid (row by row)
    std::vector<float> grid = {
        0.1f, 0.9f, 0.1f, 0.1f, // row 0: starts at (1, 0)
        0.1f, 0.9f, 0.1f, 0.1f, // row 1: goes through (1, 1)
        0.1f, 0.1f, 0.9f, 0.1f, // row 2: moves diagonally to (2, 2)
        0.1f, 0.1f, 0.9f, 0.1f  // row 3: reaches bottom edge at (2, 3)
    };

    auto path = MSMT::ASearch(grid, W, H);

    std::cout << "Path length: " << path.size() << "\n";
    for (auto [x, y] : path) {
        std::cout << "(" << x << ", " << y << ") ";
    }
    std::cout << "\n";
    return 0;
}
