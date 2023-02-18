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
	ll L, N;
	cin >> L >> N;
	int k = 1;
	while (L % N != 0) {
		N = (int)(N - L % N);
		k++;
	}
	cout << k << endl;
}
