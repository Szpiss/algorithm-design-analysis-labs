#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct Node {
    int x;
    int y;
    int dog_bites;
    int depth;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) {
        cerr << "Failed to read test count.\n";
        return 1;
    }

    const int dx[4] = {-1, 1, 0, 0};
    const int dy[4] = {0, 0, -1, 1};

    while (t--) {
        int n;
        cin >> n;
        vector<string> grid(n);
        for (int i = 0; i < n; ++i) {
            cin >> grid[i];
        }

        pair<int, int> start = {-1, -1};
        pair<int, int> target = {-1, -1};
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 'p') {
                    start = {i, j};
                } else if (grid[i][j] == 'a') {
                    target = {i, j};
                }
            }
        }

        if (start.first == -1 || target.first == -1) {
            cout << "No\n";
            continue;
        }

        vector<vector<vector<int>>> visited(n, vector<vector<int>>(n, vector<int>(2, 0)));
        queue<Node> q;
        q.push({start.first, start.second, 0, 0});
        visited[start.first][start.second][0] = 1;

        bool found = false;
        while (!q.empty() && !found) {
            Node current = q.front();
            q.pop();

            if (current.x == target.first && current.y == target.second) {
                found = true;
                break;
            }

            for (int dir = 0; dir < 4; ++dir) {
                int nx = current.x + dx[dir];
                int ny = current.y + dy[dir];

                if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
                    continue;
                }
                if (grid[nx][ny] == 'k') {
                    continue;
                }

                int next_bites = current.dog_bites + (grid[nx][ny] == 'd' ? 1 : 0);
                if (next_bites >= 2) {
                    continue;
                }
                if (visited[nx][ny][next_bites]) {
                    continue;
                }

                visited[nx][ny][next_bites] = 1;
                q.push({nx, ny, next_bites, current.depth + 1});
            }
        }

        cout << (found ? "Yes" : "No") << '\n';
    }

    return 0;
}

