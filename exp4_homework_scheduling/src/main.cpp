#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

struct Job {
    int id;
    int deadline;
    int penalty;
};

struct DisjointSet {
    vector<int> parent;

    explicit DisjointSet(int n) : parent(n + 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    void occupy(int x) {
        parent[x] = find(x - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) {
        cerr << "Failed to read test count.\n";
        return 1;
    }

    while (t--) {
        int n;
        cin >> n;
        vector<int> deadlines(n);
        vector<int> penalties(n);

        for (int i = 0; i < n; ++i) {
            cin >> deadlines[i];
        }
        for (int i = 0; i < n; ++i) {
            cin >> penalties[i];
        }

        vector<Job> jobs;
        jobs.reserve(n);
        int max_deadline = 0;
        for (int i = 0; i < n; ++i) {
            jobs.push_back({i, deadlines[i], penalties[i]});
            max_deadline = max(max_deadline, deadlines[i]);
        }

        sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
            if (a.penalty != b.penalty) {
                return a.penalty > b.penalty;
            }
            return a.deadline < b.deadline;
        });

        DisjointSet dsu(max_deadline);
        long long total_penalty = 0;

        for (const Job& job : jobs) {
            int latest_slot = dsu.find(job.deadline);
            if (latest_slot > 0) {
                dsu.occupy(latest_slot);
            } else {
                total_penalty += job.penalty;
            }
        }

        cout << total_penalty << '\n';
    }

    return 0;
}
