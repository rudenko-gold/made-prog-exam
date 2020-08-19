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
#include <assert.h>

using namespace std;

struct Ingridient {
    string name;

    vector<pair<string, long long>> needs;
};

void compute(Ingridient& ingridient, long long cnt, unordered_map<string, Ingridient>& receipts, unordered_map<string, long long>& need_to_buy) {
    string& ing_name = ingridient.name;

    if (receipts.find(ing_name) == receipts.end())  {
        need_to_buy[ing_name] += cnt;
    } else {
        for (auto& [need_ing_name, ing_cnt] : ingridient.needs) {
            if (receipts.find(need_ing_name) == receipts.end()) {
                need_to_buy[need_ing_name] += ing_cnt * cnt;
            } else {
                compute(receipts[need_ing_name], ing_cnt * cnt, receipts, need_to_buy);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_count;
    cin >> test_count;

    for (int t = 0; t < test_count; t++) {
        int n, k, f;
        cin >> n >> k >> f;

        vector<pair<string, long long>> v(n);

        for (int i = 0; i < n; ++i) {
            cin >> v[i].first >> v[i].second;
        }

        unordered_map<string, Ingridient> receipts;

        for (int i = 0; i < k; ++i) {
            string name;
            long long ingridient_count;
            cin >> name >> ingridient_count;
            receipts[name].name = name;
            receipts[name].needs.resize(ingridient_count);

            for (int j = 0; j < ingridient_count; ++j) {
                cin >> receipts[name].needs[j].first >> receipts[name].needs[j].second;
            }
        }

        vector<pair<string, long long>> fridge(f);

        for (int i = 0; i < f; ++i) {
            cin >> fridge[i].first >> fridge[i].second;
        }

        unordered_map<string, long long> need_to_buy;

        for (auto& [name, cnt] : v) {
            if (receipts.find(name) == receipts.end()) {
                need_to_buy[name] += cnt;
            } else {
                compute(receipts[name], cnt, receipts, need_to_buy);
            }
        }

        for (auto& [name, cnt] : fridge) {
            if (need_to_buy.find(name) != need_to_buy.end()) {
                if (need_to_buy[name] <= cnt) {
                    need_to_buy.erase(name);
                } else {
                    need_to_buy[name] -= cnt;
                }
            }
        }

        vector<pair<string, long long>> ans(need_to_buy.begin(), need_to_buy.end());

        sort(ans.begin(), ans.end());

        for (auto& [name, cnt] : ans) {
            cout << name << " " << cnt << "\n";
        }
    }

    return 0;
}
