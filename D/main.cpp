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
#include <stack>
#include <random>

using namespace std;

#define MAX 1000001

using namespace std;

struct node {
    long long min, add;
} SegTree[4 * MAX];

long long min(long long i, long long j) {
    return (i < j) ? i : j;
}

void build (vector<long long> &a, int v, int LeftPos, int RightPos) {
    if (LeftPos == RightPos) {
        SegTree[v].min = a[LeftPos];
        SegTree[v].add = 0;
    } else {
        int Middle = (LeftPos + RightPos) / 2;
        build (a, v * 2, LeftPos, Middle);
        build (a, v * 2 + 1, Middle+1, RightPos);

        SegTree[v].min = min(SegTree[v * 2].min,SegTree[v * 2 + 1].min);
        SegTree[v].add = 0;
    }
}

void Push(int v, int LeftPos, int Middle, int RightPos) {
    if (SegTree[v].add) {
        SegTree[2 * v].add += SegTree[v].add;
        SegTree[2 * v].min += SegTree[v].add;

        SegTree[2 * v + 1].add += SegTree[v].add;
        SegTree[2 * v + 1].min += SegTree[v].add;
        SegTree[v].add = 0;
    }
}

void AddValue(int v, int LeftPos, int RightPos,
              int L, int R, long long Value) {
    if (L > R) return;
    if ((LeftPos == L) && (RightPos == R)) {
        SegTree[v].add += Value;
        SegTree[v].min += Value;
        return;
    }

    int Middle = (LeftPos + RightPos) / 2;
    Push(v,LeftPos,Middle,RightPos);
    AddValue(2 * v, LeftPos, Middle, L, min(Middle,  R), Value);
    AddValue(2 * v + 1, Middle+1, RightPos, max(L,Middle + 1), R, Value);

    SegTree[v].min = min(SegTree[2 * v].min, SegTree[2 * v + 1].min);
}

struct Tag {
    string name;
    bool is_open;

    string to_string() {
        if (is_open) {
            return "<" + name + ">";
        } else {
            return "</" + name + ">";
        }
    }
};

string to_upper(string s) {
    for (auto& ch : s) {
        ch = toupper(ch);
    }
    return s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_count;
    cin >> test_count;
    std::random_device r;
    default_random_engine generator(r());
    uniform_int_distribution<long long> distribution(1ll, 100000000ll);

    for (int t = 0; t < test_count; t++) {
        int line_cnt;
        cin >> line_cnt;

        vector<Tag> v;
        for (int i = 0; i < line_cnt; i++) {
            string line;
            cin >> line;
            if (line[1] == '/') {
                v.push_back({to_upper(line.substr(2, line.size() - 3)), false});
            } else {
                v.push_back({to_upper(line.substr(1, line.size() - 2)), true});
            }
        }

        unordered_map<string, long long> dict;
        unordered_set<long long> used;
        for (auto& tag : v) {
            if (dict.find(tag.name) == dict.end()) {
                while (true) {
                    long long p = distribution(generator);
                    if (used.find(p) == used.end()) {
                        dict[tag.name] = p;
                        used.insert(p);
                        break;
                    }
                }
            }
        }
        long long sum = 0;
        vector<long long> pref;

        for (auto& tag : v) {
            if (tag.is_open) {
                sum += dict[tag.name];
            } else {
                sum -= dict[tag.name];
            }
            pref.push_back(sum);
        }

        build(pref, 1, 0, (int)v.size() - 1);
        int status = 0;

        if (SegTree[1].min >= 0 && sum == 0) {
            status = 1;
            cout << "CORRECT\n";
        } else {
            for (size_t i = 0; i < v.size(); i++) {
                if (v[i].is_open) {
                    AddValue(1,0,(int)pref.size()-1,i,(int)pref.size()-1,dict[v[i].name] * -1);
                    sum -= dict[v[i].name];
                    //cout << v[i].name << " " << SegTree[1].min << " " << sum << " " << dict[v[i].name] << endl;
                    if ((SegTree[1].min >= 0) && (sum == 0)) {
                        cout << "ALMOST " << v[i].to_string() << "\n";
                        status = 2;
                        break;
                    }

                    sum += dict[v[i].name];
                    AddValue(1,0,(int)pref.size()-1,i,(int)pref.size()-1,dict[v[i].name] * 1);
                } else {
                    AddValue(1,0,(int)pref.size()-1,i,(int)pref.size()-1,dict[v[i].name] * 1);
                    sum += dict[v[i].name];
                    //cout << v[i].name << " " << SegTree[1].min << " " << sum << " " << dict[v[i].name] << endl;
                    if ((SegTree[1].min >= 0) && (sum == 0)) {
                        cout << "ALMOST " << v[i].to_string() << "\n";
                        status = 2;
                        break;
                    }

                    sum -= dict[v[i].name];
                    AddValue(1,0,(int)pref.size()-1,i,(int)pref.size()-1,dict[v[i].name] * -1);
                }
            }
        }
        if (status == 0) {
            cout << "INCORRECT\n";
        }
    }

    return 0;
}
