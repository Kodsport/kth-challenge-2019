#include <bits/stdc++.h>
using namespace std;

struct scc {
	int n, C = 0, T = 0, top = -1;
	vector<int> comp, t, st;
	vector<vector<int>> adj;

	int dfs(int i) {
		int tmin = t[i] = T++;
		st[++top] = i;
		for (int j: adj[i]) if (comp[j] == -1) {
			tmin = min(tmin, t[j] == -1 ? dfs(j) : t[j]);
		}
		if (tmin == t[i]) {
			while (st[top] != i) comp[st[top--]] = C;
			comp[st[top--]] = C++;
		}
		return tmin;
	}

	scc(vector<vector<int>> adj): n(adj.size()), comp(n,-1), t(n,-1), st(n), adj(adj) {
		for (int i = 0; i < n; i++) if (t[i] == -1) dfs(i);
	}
};

struct sat2 {
	int n;
	vector<vector<int>> adj;
	vector<int> val;
	sat2(int n): n(n), adj(2*n), val(n) { }

	void add(int a, int b) { adj[n+a].push_back(n+b), adj[n+~b].push_back(n+~a); }

	void Or   (int a, int b) { add(~a,b); }
	void True (int a)        { Or(a,a); }
	void False(int a)        { True(~a); }
	void Same (int a, int b) { add(a,b), add(b,a); }
	void Xor  (int a, int b) { Same(a,~b); }

	bool check() {
		scc s(adj);
		for (int i = 0; i < n; i++) if (s.comp[n+~i] == s.comp[n+i]) return false;
		for (int i = 0; i < n; i++) val[i] = s.comp[n+~i] > s.comp[n+i];
		return true;
	}
};

int main() {
	int n, m; cin >> n >> m;

	auto id = [&](int i, char c) {
		return 2*i + (c == '+');
	};
	
	sat2 S(2*n);
	vector<bool> zero(n,true);
	
	for (int i = 0; i < n; i++) S.Or(~id(i,'+'),~id(i,'-'));

	while (m--) {
		int i, j; cin >> i >> j;
		i--, j--;
		char c; cin >> c;
		
		if (c != 'x') {
			zero[i] = zero[j] = false;
		}
		if (c == '+') {
			S.Or(id(i,'+'), id(j,'+'));
			S.False(id(i,'-'));
			S.False(id(j,'-'));
		}
		if (c == '=') {
			S.Same(id(i,'+'),id(j,'-'));
			S.Same(id(i,'-'),id(j,'+'));
		}
		if (c == '-') {
			S.Or(id(i,'-'), id(j,'-'));
			S.False(id(i,'+'));
			S.False(id(j,'+'));
		}
	}
	
	assert(S.check());
	for (int i = 0; i < n; i++) {
		if (zero[i]) cout << 'x';
		else if (S.val[id(i,'+')]) cout << '+';
		else if (S.val[id(i,'-')]) cout << '-';
		else cout << '=';
	}
	cout << endl;
}
