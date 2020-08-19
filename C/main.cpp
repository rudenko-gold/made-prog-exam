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

long long gcd(long long a, long long b) {
    a = abs(a);
    b = abs(b);

    while (a && b) {
        a %= b;
        swap(a, b);
    }
    return a + b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t test_count;
    cin >> test_count;

    for (size_t t = 0; t < test_count; ++t) {
        long long h;
        cin >> h;
        long long numerator = 0, denominator = 1ull << (h - 1);
        vector<vector<long long>> dp(h, vector<long long>(h + 1, 0));

        dp[0][0] = 1;

        for (size_t i = 0; i + 1 < h; ++i) {
            for (size_t j = 0; j <= i; ++j) {
                dp[i + 1][j] += dp[i][j];
                dp[i + 1][j + 1] += dp[i][j];
                dp[i][j] *= 1ull << (h - i - 1);
            }
        }

        for (size_t i = 0; i < h; ++i) {
            for (size_t j = 0; j <= i; ++j) {
                long long item;
                cin >> item;
                numerator += item * dp[i][j];
            }
        }

        long long g = gcd(numerator, denominator);
        numerator /= g;
        denominator /= g;

        cout << numerator << " " << denominator << "\n";

    }

    return 0;
}
