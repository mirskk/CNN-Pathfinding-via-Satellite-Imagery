#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
// A star algorithm for traversal
struct MSMT {
    int x, y;
    float f; // cost acculumation
    float h; // estimated distance to nearest target

    //take minimum f+h
    bool operator>(const MSMT &other) const { return (f + h) > (other.f + other.h); }
    
    static std::vector<std::pair<int, int>> ASearch( const std::vector<float>& probability, int W, int H) {
        using A = std::priority_queue<MSMT, std::vector<MSMT>, std::greater<MSMT>>;

        A frontier; // grid of tiles to explore next
        std::vector<bool> explored(W * H, false); // coordinates we're done with
        std::vector<float> bestG(W * H, 1e9f); // cheapest cost found so far to reach each tile from start
        std::vector<int> parent(W * H, -1); // means of retracing the path back, flags for the way back

        //lambda
        //[&] - capture by reference
        auto heuristic = [&] (int x, int y) {
            return static_cast<float>(std::min(W - 1 - x, H - 1 - y));
        };

        auto stepCost = [&] (int idx) {
            float p = std::clamp(probability[idx], 0.01f, 0.99f);
            return (1.0f - p) * 10.0f + 0.1f;
        };

        for (int i = 0; i < W; i++) {
            if (probability[i] > 0.5f) {
                bestG[i] = stepCost(i);
                frontier.push(MSMT{i, 0, bestG[i], heuristic(i, 0)});
            }
        }

        const int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
        const int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
        const float costs[8] = {1.414f, 1.0f, 1.414f, 1.0f, 1.0f, 1.414f, 1.0f, 1.414f}; //pithagorean theorem for diagonal movement

        while (!frontier.empty()) {
            MSMT m = frontier.top();
            frontier.pop();
            int midx = m.y * W + m.x;
            if (explored[midx]) continue;
            explored[midx] = true;

            if ((m.x == W-1 || m.y == H-1) && probability[midx] > 0.5f) {
                std::vector<std::pair<int, int>> finalPath;
                for (int c = midx; c != -1; c = parent[c] ) {
                    finalPath.push_back({c % W, c / W});
                }
                std::reverse(finalPath.begin(), finalPath.end());
                return finalPath;
            }

            for (int a  = 0; a < 8; ++a) {
                int nx = m.x + dx[a];
                int ny = m.y + dy[a];

                if (nx < 0 || ny < 0 || nx >= W || ny >= H) {
                    continue;
                }
                int nidx = ny * W + nx;
                if (explored[nidx]) continue;

                float newG = m.f + costs[a] * stepCost(nidx);
                if (newG < bestG[nidx]) {
                    bestG[nidx] = newG;
                    parent[nidx] = midx;
                    frontier.push({nx, ny, newG, heuristic(nx, ny)});
                }
            }
        }
        return {};
    }
};
