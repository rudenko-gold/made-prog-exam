#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <deque>
#include <list>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t test_counts;
    cin >> test_counts;
    for (size_t q = 0; q < test_counts; ++q) {
        map<pair<long long, long long>, long long> freq;
        int k;
        cin >> k;
        long long ans = 0;
        for (size_t i = 0; i < k; ++i) {
            pair<long long, long long> point;
            cin >> point.first >> point.second;
            freq[point]++;
        }

        for (auto iter1 = freq.begin(); iter1 != freq.end(); iter1++) {
            for (auto iter2 = next(iter1); iter2 != freq.end(); iter2++)  {
                auto p1 = *iter1;
                auto p2 = *iter2;
                if (p1 != p2) {
                    auto [x1, y1] = p1.first;
                    auto [x2, y2] = p2.first;
                    if (x1 != x2 && y1 != y2 && freq.count({x1, y2}) && freq.count({x2, y1})) {
                        ans += p1.second * p2.second * freq.count({x1, y2}) * freq.count({x2, y1});
                        //cout << "(" << x1 << ", " << y1 << ") & (" << x2 << ", " << y2 << ")\n";
                    }
                }
            }
        }

        cout << ans / 2ll << "\n";
    }

    return 0;
}
