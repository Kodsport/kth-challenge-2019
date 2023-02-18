#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

vi match;
vector<bool> seen;
bool find(int j, const vector<vi>& g) {
	if (match[j] == -1) return 1;
	seen[j] = 1; int di = match[j];
	trav(e, g[di])
		if (!seen[e] && find(e, g)) {
			match[e] = di;
			return 1;
		}
	return 0;
}
int dfs_matching(const vector<vi>& g, int n, int m) {
	match.assign(m, -1);
	rep(i,0,n) {
		seen.assign(m, 0);
		trav(j,g[i])
			if (find(j, g)) {
				match[j] = i;
				break;
			}
	}
	return m - (int)count(all(match), -1);
}

vi cover(vector<vi>& g, int n, int m) {
	int res = dfs_matching(g, n, m);
	seen.assign(m, false);
	vector<bool> lfound(n, true);
	trav(it, match) if (it != -1) lfound[it] = false;
	vi q, cover;
	rep(i,0,n) if (lfound[i]) q.push_back(i);
	while (!q.empty()) {
		int i = q.back(); q.pop_back();
		lfound[i] = 1;
		trav(e, g[i]) if (!seen[e] && match[e] != -1) {
			seen[e] = true;
			q.push_back(match[e]);
		}
	}
	rep(i,0,n) if (!lfound[i]) cover.push_back(i);
	rep(i,0,m) if (seen[i]) cover.push_back(n+i);
	assert(sz(cover) == res);
	return cover;
}

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
	int N, M;
	cin >> N >> M;

	vector<string> grid(N);
	rep(i,0,N) cin >> grid[i];

	map<pii, int> inds[2];

	auto find = [&](int i, int j) {
		if (i < 0 || j < 0 || i >= N || j >= M) return -1;
		if (grid[i][j] == '#') return -1;
		int parity = (i^j) & 1;
		int& out = inds[parity][pii(i,j)];
		if (!out) out = sz(inds[parity]);
		return out-1;
	};

	rep(i,0,N) rep(j,0,M) find(i, j);
	int left = sz(inds[0]);
	int right = sz(inds[1]);
	vector<vi> gr(left);

	rep(i,0,N) rep(j,0,M) if (((i^j) & 1) == 0) {
		int x = find(i, j);
		if (x == -1) continue;
		int DX[] = {0,0,1,-1};
		int DY[] = {1,-1,0,0};
		rep(d,0,4) {
			int y = find(i + DX[d], j + DY[d]);
			if (y == -1) continue;
			gr[x].push_back(y);
		}
	}

	vi c = cover(gr, left, right);
	set<int> cc(all(c));
	rep(i,0,N) rep(j,0,M) {
		int x = find(i, j);
		if (x == -1) continue;
		if ((i^j) & 1) x += left;
		if (cc.count(x)) continue;
		grid[i][j] = 'E';
	}
	rep(i,0,N) cout << grid[i] << endl;
}
