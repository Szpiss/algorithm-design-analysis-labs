#include <cmath>
#include <iostream>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

enum class Outcome {
    LeftHeavier,
    RightHeavier,
    Balance
};

struct Answer {
    int coin = -1;
    string type;
};

class CounterfeitFinder {
public:
    explicit CounterfeitFinder(vector<int> weights) : weights_(std::move(weights)) {}

    Answer solve() {
        vector<int> all(weights_.size());
        iota(all.begin(), all.end(), 0);
        vector<int> genuine;
        return searchUnknown(all, genuine);
    }

    int weighCount() const { return weigh_count_; }

    const vector<string>& logs() const { return logs_; }

private:
    vector<int> weights_;
    int weigh_count_ = 0;
    vector<string> logs_;

    static vector<int> slice(const vector<int>& source, size_t begin, size_t end) {
        return vector<int>(source.begin() + static_cast<long>(begin),
                           source.begin() + static_cast<long>(end));
    }

    static vector<int> mergeVectors(const vector<int>& a, const vector<int>& b) {
        vector<int> result = a;
        result.insert(result.end(), b.begin(), b.end());
        return result;
    }

    static vector<int> mergeVectors(const vector<int>& a, const vector<int>& b, const vector<int>& c) {
        vector<int> result = a;
        result.insert(result.end(), b.begin(), b.end());
        result.insert(result.end(), c.begin(), c.end());
        return result;
    }

    static string joinCoins(const vector<int>& coins) {
        if (coins.empty()) {
            return "{}";
        }
        ostringstream out;
        out << "{";
        for (size_t i = 0; i < coins.size(); ++i) {
            if (i) {
                out << ", ";
            }
            out << coins[i];
        }
        out << "}";
        return out.str();
    }

    static string outcomeToString(Outcome outcome) {
        switch (outcome) {
            case Outcome::LeftHeavier:
                return "left heavier";
            case Outcome::RightHeavier:
                return "right heavier";
            case Outcome::Balance:
                return "balance";
        }
        return "unknown";
    }

    void splitThree(const vector<int>& coins, vector<int>& a, vector<int>& b, vector<int>& c) const {
        size_t k = coins.size() / 3;
        a = slice(coins, 0, k);
        b = slice(coins, k, 2 * k);
        c = slice(coins, 2 * k, coins.size());
    }

    Outcome compareGroups(const vector<int>& left, const vector<int>& right) {
        int left_sum = 0;
        int right_sum = 0;
        for (int coin : left) {
            left_sum += weights_[coin];
        }
        for (int coin : right) {
            right_sum += weights_[coin];
        }

        Outcome outcome = Outcome::Balance;
        if (left_sum > right_sum) {
            outcome = Outcome::LeftHeavier;
        } else if (left_sum < right_sum) {
            outcome = Outcome::RightHeavier;
        }

        ++weigh_count_;
        ostringstream out;
        out << "Weigh " << weigh_count_ << ": " << joinCoins(left) << " vs " << joinCoins(right)
            << " -> " << outcomeToString(outcome);
        logs_.push_back(out.str());
        return outcome;
    }

    Answer identifyByGenuine(int coin, int genuine) {
        Outcome outcome = compareGroups({coin}, {genuine});
        if (outcome == Outcome::LeftHeavier) {
            return {coin, "heavier"};
        }
        if (outcome == Outcome::RightHeavier) {
            return {coin, "lighter"};
        }
        throw runtime_error("Failed to identify counterfeit coin.");
    }

    Answer bruteForcePolarized(const vector<int>& heavy, const vector<int>& light, const vector<int>& genuine) {
        if (genuine.empty()) {
            throw runtime_error("No genuine coin available for polarized brute force.");
        }
        int g = genuine.front();
        for (int coin : heavy) {
            Outcome outcome = compareGroups({coin}, {g});
            if (outcome == Outcome::LeftHeavier) {
                return {coin, "heavier"};
            }
        }
        for (int coin : light) {
            Outcome outcome = compareGroups({coin}, {g});
            if (outcome == Outcome::RightHeavier) {
                return {coin, "lighter"};
            }
        }
        throw runtime_error("Counterfeit coin not found in polarized brute force.");
    }

    Answer searchKnown(const vector<int>& suspects, bool heavier) {
        if (suspects.empty()) {
            throw runtime_error("Known-direction search received no suspects.");
        }
        if (suspects.size() == 1) {
            return {suspects.front(), heavier ? "heavier" : "lighter"};
        }
        if (suspects.size() == 2) {
            Outcome outcome = compareGroups({suspects[0]}, {suspects[1]});
            if (heavier) {
                return outcome == Outcome::LeftHeavier ? Answer{suspects[0], "heavier"}
                                                       : Answer{suspects[1], "heavier"};
            }
            return outcome == Outcome::LeftHeavier ? Answer{suspects[1], "lighter"}
                                                   : Answer{suspects[0], "lighter"};
        }

        vector<int> a, b, c;
        splitThree(suspects, a, b, c);
        Outcome outcome = compareGroups(a, b);

        if (heavier) {
            if (outcome == Outcome::Balance) {
                return searchKnown(c, true);
            }
            if (outcome == Outcome::LeftHeavier) {
                return searchKnown(a, true);
            }
            return searchKnown(b, true);
        }

        if (outcome == Outcome::Balance) {
            return searchKnown(c, false);
        }
        if (outcome == Outcome::LeftHeavier) {
            return searchKnown(b, false);
        }
        return searchKnown(a, false);
    }

    Answer searchPolarized(const vector<int>& heavy, const vector<int>& light, const vector<int>& genuine) {
        if (heavy.empty() && light.empty()) {
            throw runtime_error("Polarized search received no suspects.");
        }
        if (heavy.empty()) {
            return searchKnown(light, false);
        }
        if (light.empty()) {
            return searchKnown(heavy, true);
        }
        if (heavy.size() + light.size() <= 3 || (heavy.size() / 3 == 0 && light.size() / 3 == 0)) {
            return bruteForcePolarized(heavy, light, genuine);
        }

        vector<int> h1, h2, h3;
        vector<int> l1, l2, l3;
        splitThree(heavy, h1, h2, h3);
        splitThree(light, l1, l2, l3);

        vector<int> left = mergeVectors(h1, l2);
        vector<int> right = mergeVectors(h2, l1);
        Outcome outcome = compareGroups(left, right);

        if (outcome == Outcome::LeftHeavier) {
            return searchPolarized(h1, l1, mergeVectors(genuine, h2, mergeVectors(h3, mergeVectors(l2, l3))));
        }
        if (outcome == Outcome::RightHeavier) {
            return searchPolarized(h2, l2, mergeVectors(genuine, h1, mergeVectors(h3, mergeVectors(l1, l3))));
        }
        return searchPolarized(h3, l3, mergeVectors(genuine, h1, mergeVectors(h2, mergeVectors(l1, l2))));
    }

    Answer searchUnknown(const vector<int>& suspects, const vector<int>& genuine) {
        if (suspects.empty()) {
            throw runtime_error("Unknown search received no suspects.");
        }
        if (suspects.size() == 1) {
            if (genuine.empty()) {
                throw runtime_error("No genuine coin available to identify type.");
            }
            return identifyByGenuine(suspects.front(), genuine.front());
        }
        if (suspects.size() == 2) {
            if (genuine.empty()) {
                throw runtime_error("No genuine coin available for two-suspect resolution.");
            }
            Outcome first = compareGroups({suspects[0]}, {genuine.front()});
            if (first == Outcome::Balance) {
                return identifyByGenuine(suspects[1], genuine.front());
            }
            return first == Outcome::LeftHeavier ? Answer{suspects[0], "heavier"}
                                                 : Answer{suspects[0], "lighter"};
        }

        vector<int> a, b, c;
        splitThree(suspects, a, b, c);
        Outcome outcome = compareGroups(a, b);

        if (outcome == Outcome::Balance) {
            return searchUnknown(c, mergeVectors(genuine, a, b));
        }
        if (outcome == Outcome::LeftHeavier) {
            return searchPolarized(a, b, mergeVectors(genuine, c));
        }
        return searchPolarized(b, a, mergeVectors(genuine, c));
    }
};

static int theoreticalLowerBound(int n) {
    int steps = 0;
    long long states = 1;
    while (states < 2LL * n) {
        states *= 3;
        ++steps;
    }
    return steps;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) {
        cerr << "Failed to read test count.\n";
        return 1;
    }

    for (int case_id = 1; case_id <= t; ++case_id) {
        int n, fake_index;
        char type;
        cin >> n >> fake_index >> type;
        if (n <= 3 || fake_index < 0 || fake_index >= n || (type != 'H' && type != 'L')) {
            cerr << "Invalid input at case " << case_id << ".\n";
            return 1;
        }

        vector<int> weights(n, 10);
        weights[fake_index] = (type == 'H') ? 11 : 9;

        CounterfeitFinder finder(weights);
        Answer answer = finder.solve();

        cout << "Case " << case_id << ":\n";
        for (const string& line : finder.logs()) {
            cout << "  " << line << '\n';
        }
        cout << "  Result: coin " << answer.coin << " is " << answer.type << ".\n";
        cout << "  Weighings used: " << finder.weighCount() << '\n';
        cout << "  Theoretical lower bound: " << theoreticalLowerBound(n) << "\n\n";
    }

    return 0;
}

