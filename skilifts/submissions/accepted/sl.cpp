#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
	int N;
	cin >> N;
	map<int, pii> pyl;
	rep(i,0,N) {
		int x, y, r;
		cin >> x >> y >> r;
		if (r == 1) pyl[y].first++;
		else pyl[y].second++;
	}
	int res = 0;
	trav(pa, pyl) {
		int y = pa.first;
		pii co = pa.second;
		int up = co.first + co.second;
		if (up && pyl.count(y+1)) {
			pii& co2 = pyl[y+1];
			if (up < co2.second) {
				res += up;
			} else {
				res += co2.second;
				up -= co2.second;
				int use = min(up, co2.first);
				res += use;
				co2.first -= use;
			}
		}
	}
	cout << res << endl;
}
