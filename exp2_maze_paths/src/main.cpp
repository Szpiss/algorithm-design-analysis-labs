#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;
};

static string pathToString(const vector<Point>& path) {
    string result;
    for (size_t i = 0; i < path.size(); ++i) {
        if (i) {
            result += " -> ";
        }
        result += "(" + to_string(path[i].x) + ", " + to_string(path[i].y) + ")";
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    if (!(cin >> m >> n)) {
        cerr << "Failed to read maze size.\n";
        return 1;
    }

    vector<vector<int>> maze(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> maze[i][j];
        }
    }

    Point start{}, target{};
    cin >> start.x >> start.y >> target.x >> target.y;

    auto inBounds = [&](int x, int y) {
        return x >= 0 && x < m && y >= 0 && y < n;
    };

    if (!inBounds(start.x, start.y) || !inBounds(target.x, target.y) ||
        maze[start.x][start.y] == 1 || maze[target.x][target.y] == 1) {
        cerr << "Invalid start or target position.\n";
        return 1;
    }

    vector<vector<int>> visited(m, vector<int>(n, 0));
    vector<Point> current_path;
    vector<vector<Point>> all_paths;
    vector<Point> shortest_path;
    const int dx[4] = {-1, 1, 0, 0};
    const int dy[4] = {0, 0, -1, 1};

    auto dfs = [&](auto&& self, int x, int y) -> void {
        visited[x][y] = 1;
        current_path.push_back({x, y});

        if (x == target.x && y == target.y) {
            all_paths.push_back(current_path);
            if (shortest_path.empty() || current_path.size() < shortest_path.size()) {
                shortest_path = current_path;
            }
        } else {
            for (int dir = 0; dir < 4; ++dir) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                if (inBounds(nx, ny) && !visited[nx][ny] && maze[nx][ny] == 0) {
                    self(self, nx, ny);
                }
            }
        }

        current_path.pop_back();
        visited[x][y] = 0;
    };

    dfs(dfs, start.x, start.y);

    if (all_paths.empty()) {
        cout << "No path found.\n";
        return 0;
    }

    cout << "Total paths: " << all_paths.size() << '\n';
    for (size_t i = 0; i < all_paths.size(); ++i) {
        cout << "Path " << i + 1 << ": " << pathToString(all_paths[i]) << '\n';
    }

    cout << "Shortest path length: " << shortest_path.size() - 1 << '\n';
    cout << "Shortest path: " << pathToString(shortest_path) << '\n';

    return 0;
}

