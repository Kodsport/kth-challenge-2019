#include <bits/stdc++.h>

using namespace std;

const char *effects = "x-=+";
const int mask[4] = {15, 6, 14, 12};
const int order[4] = {0, 1, 3, 2};

int main(void) {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> poss(n+1, 15);
    vector<vector<int>> opp(n+1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        char eff[10];
        scanf("%d%d%s", &u, &v, eff);
        int f = strchr(effects, *eff) - effects;
        poss[u] &= mask[f];
        poss[v] &= mask[f];
        if (f == 2) {
            opp[u].push_back(v);
            opp[v].push_back(u);
        }
    }

    string res(n+1, ' ');

    auto assign = [&](int u, int val) {
        vector<pair<int, int>> Q;
        Q.push_back({u, val});
        while (!Q.empty()) {
            tie(u, val) = Q.back();
            Q.pop_back();
            // if (res[u] == effects[val]) continue; //oops
            if (!(poss[u] & (1<<val))) return false;
            res[u] = effects[val];
            for (int v: opp[u])
                if (res[v] != effects[4-val]) {
                    if ((val == 1 || val == 3) && res[v] == res[u]) return false;
                    Q.push_back({v, 4-val});
                }
        }
        return true;
    };

    vector<int> idxs(n);
    iota(idxs.begin(), idxs.end(), 1);
    sort(idxs.begin(), idxs.end(), [&](int u, int v) { return poss[u] < poss[v]; });
    for (int u: idxs) {
        if (res[u] != ' ') continue;
        for (int i: order)
            if (poss[u] & (1<<i)) {
                if (!assign(u, i))
                    assign(u, 2);
                break;
            }
    }
    printf("%s\n", res.substr(1).c_str());
}
