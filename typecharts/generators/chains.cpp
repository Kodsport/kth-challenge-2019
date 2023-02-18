#include <bits/stdc++.h>
using namespace std;

char combine(char a, char b) {
	if (a == 'x' || b == 'x') return 'x';
	if (a == b) return a;
	if (a != '+' && b != '+') return '-';
	if (a != '-' && b != '-') return '+';
	return '=';
}

int main() {
	int n = 100000;
	int seed; cin >> seed;

	mt19937_64 gen(seed);
	
	string types(n,' ');
	uniform_int_distribution<int> typedis(0,3);
	for (char &c: types) c = "x-=+"[typedis(gen)];
	
	int k = n/10;
	vector<bool> split(n-1);
	uniform_int_distribution<int> dis(0,n-2);
	while (k--) split[dis(gen)] = true;
	
	vector<int> perm(n);
	iota(begin(perm),end(perm),0);
	shuffle(begin(perm),end(perm),gen);

	vector<tuple<int,int,char>> edges;
	for (int i = 0; i+1 < n; i++) {
		if (split[i]) continue;
		edges.emplace_back(perm[i]+1, perm[i+1]+1, combine(types[i],types[i+1]));
	}
	shuffle(begin(edges),end(edges),gen);
	
	int m = n-1-accumulate(begin(split),end(split),0);
	cout << n << " " << m << endl;
	for (auto e: edges) {
		cout << get<0>(e) << " " << get<1>(e) << " " << get<2>(e) << endl;
	}
}
