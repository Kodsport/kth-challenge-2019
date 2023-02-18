// 2-SAT solution based on having a + and a - variable per unknown.
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

// https://github.com/kth-competitive-programming/kactl/blob/master/content/graph/2sat.h
struct TwoSat {
	int N;
	vector<vi> gr;
	vi values;

	TwoSat(int n = 0) : N(n), gr(2*n) {}

	void either(int f, int j) {
		f = max(2*f, -1-2*f);
		j = max(2*j, -1-2*j);
		gr[f^1].push_back(j);
		gr[j^1].push_back(f);
	}
	void set_value(int x) { either(x, x); }
	void equal(int x, int y) {
		either(x, ~y);
		either(y, ~x);
	}

	vi val, comp, z; int time = 0;
	int dfs(int i) {
		int low = val[i] = ++time, x; z.push_back(i);
		trav(e, gr[i]) if (!comp[e])
			low = min(low, val[e] ?: dfs(e));
		++time;
		if (low == val[i]) do {
			x = z.back(); z.pop_back();
			comp[x] = time;
			if (values[x>>1] == -1)
				values[x>>1] = !(x&1);
		} while (x != i);
		return val[i] = low;
	}

	bool solve() {
		values.assign(N, -1);
		val.assign(2*N, 0); comp = val;
		rep(i,0,2*N) if (!comp[i]) dfs(i);
		rep(i,0,N) if (comp[2*i] == comp[2*i+1]) return 0;
		return 1;
	}
};

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
	int N, M;
	cin >> N >> M;
	vi zero(N, true);
	TwoSat ts(2*N);
#define GOOD(i) (i)
#define BAD(i) (i + N)
	rep(i,0,N) {
		ts.either(~GOOD(i), ~BAD(i));
	}
	rep(i,0,M) {
		int a, b;
		char c;
		cin >> a >> b >> c;
		--a, --b;
		if (c == 'x') continue;
		zero[a] = false;
		zero[b] = false;
		if (c == '+') {
			ts.set_value(~BAD(a));
			ts.set_value(~BAD(b));
			ts.either(GOOD(a), GOOD(b));
		} else if (c == '-') {
			ts.set_value(~GOOD(a));
			ts.set_value(~GOOD(b));
			ts.either(BAD(a), BAD(b));
		} else {
			assert(c == '=');
			ts.equal(GOOD(a), BAD(b));
			ts.equal(BAD(a), GOOD(b));
		}
	}

	bool r = ts.solve();
	assert(r);

	rep(i,0,N) {
		if (zero[i]) cout << 'x';
		else {
			if (ts.values[GOOD(i)]) cout << '+';
			else if (ts.values[BAD(i)]) cout << '-';
			else cout << '=';
		}
	}
	cout << endl;
}
