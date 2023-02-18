// Solution based on case enumeration
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int N;
string str;
string target = "meow";

bool sol0() {
	return str.find("meow") != string::npos;
}

bool matchBefore(int i, int cnt) {
	return (i - cnt >= 0 && str.substr(i - cnt, cnt) == target.substr(0, cnt));
}

bool matchAfter(int i, int cnt) {
	return (i + cnt <= N && str.substr(i, cnt) == target.substr(4-cnt));
}

int matchBefore2(int i, int cnt) {
	if (i - cnt < 0) return 5;
	int ret = 0;
	rep(j,0,cnt) ret += (str[i - cnt + j] != target[j]);
	return ret;
}

int matchAfter2(int i, int cnt) {
	if (i + cnt > N) return 5;
	int ret = 0;
	rep(j,0,cnt) ret += (str[i + j] != target[4-cnt + j]);
	return ret;
}

bool sol1() {
	rep(which,0,4) rep(i,0,N) {
		// Replace pos i
		if (matchBefore(i, which) && matchAfter(i+1, 4-which-1))
			return true;
	}
	rep(which,0,5) rep(i,0,N) {
		// Delete pos i
		if (matchBefore(i, which) && matchAfter(i+1, 4-which))
			return true;
	}
	rep(which,0,4) rep(i,0,N+1) {
		// Insert pos i
		if (matchBefore(i, which) && matchAfter(i, 4-which-1))
			return true;
	}
	rep(which,0,3) rep(i,0,N-1) {
		// Transpose pos i
		if (matchBefore(i, which) && matchAfter(i+2, 4-which-2) && str[i] == target[which+1] && str[i+1] == target[which])
			return true;
	}
	return false;
}

bool sol2() {
	// transpose + transpose: never needed
	// transpose + erase within:
	rep(which,0,3) rep(i,1,N-1) {
		if (str[i+1] == target[which] && str[i-1] == target[which+1] && matchBefore(i-1, which) && matchAfter(i+2, 4-which-2))
			return true;
	}
	// transpose + insert within:
	rep(which,0,2) rep(i,0,N-1) {
		if (str[i+1] == target[which] && str[i] == target[which+2] && matchBefore(i, which) && matchAfter(i+2, 4-which-3))
			return true;
	}
	// transpose + side op:
	rep(which,0,3) rep(i,0,N-1) {
		if (str[i+1] == target[which] && str[i] == target[which+1]) {
			if (which == 1) {
				int costLeft = (i > 0 && target[which-1] == str[i-1] ? 0 : 1);
				int costRight = (target[which+2] == str[i+2] ? 0 : 1);
				if (costLeft + costRight <= 1) return true;
			}
			else if (which == 2) {
				if (i >= 1 && target[1] == str[i-1]) return true; // insert before e
				if (i >= 2 && target[0] == str[i-2]) return true; // replace e
				if (i >= 3 && target[1] == str[i-2] && target[0] == str[i-3]) return true; // delete
				if (i >= 1 && target[0] == str[i-1]) return true; // insert e
			}
			else if (which == 0) {
				if (target[2] == str[i+2]) return true; // insert after o
				if (target[3] == str[i+3]) return true; // replace o
				if (target[2] == str[i+3] && target[3] == str[i+4]) return true; // delete
				if (target[3] == str[i+2]) return true; // insert o
			}
		}
	}
	// transpose not needed!
	// replace:
	rep(which,0,4) rep(i,0,N) {
		// Replace pos i
		if (matchBefore2(i, which) + matchAfter2(i+1, 4-which-1) <= 1)
			return true;
	}
	rep(which,0,5) rep(i,0,N) {
		// Delete pos i
		if (matchBefore2(i, which) + matchAfter2(i+1, 4-which) <= 1)
			return true;
	}
	rep(which,0,4) rep(i,0,N+1) {
		// Insert pos i
		if (matchBefore2(i, which) + matchAfter2(i, 4-which-1) <= 1)
			return true;
	}
	// replace not needed!
	// insert + insert:
	rep(w0,0,4) rep(w1,w0+1,4) {
		string sb;
		sb += target[w0];
		sb += target[w1];
		if (str.find(sb) != string::npos) return true;
	}
	// delete + delete: not necessary, must have m#e#o#w, but can use inserts if two in a row
	// delete + insert: not necessary, must have e.g. m#e|w, but can use two inserts instead
	return false;
}

bool sol3() {
	trav(x, str) {
		if (x == 'm' || x == 'e' || x == 'o' || x == 'w') return true;
	}
	return false;
}

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
	cin >> str;
	N = sz(str);
	str += 'X';
	str += 'X';
	str += 'X';
	if (sol0()) cout << 0 << endl;
	else if (sol1()) cout << 1 << endl;
	else if (sol2()) cout << 2 << endl;
	else if (sol3()) cout << 3 << endl;
	else cout << 4 << endl;
}
