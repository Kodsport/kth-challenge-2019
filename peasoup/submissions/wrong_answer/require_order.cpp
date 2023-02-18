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
	rep(i,0,N) {
		int K;
		cin >> K;
		cin.ignore();
		string name;
		getline(cin, name);
		bool a = false, b = false;
		rep(j,0,K) {
			string line;
			getline(cin, line);
			if (line == "pea soup") a = true;
			if (line == "pancakes" && a) b = true;
		}
		if (a && b) {
			cout << name << endl;
			return 0;
		}
	}
	cout << "Anywhere is fine I guess" << endl;
}
