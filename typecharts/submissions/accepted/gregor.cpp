#include <bits/stdc++.h>

using namespace std;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const double PI = 2.0 * acos(0.0);


typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<string> vs;

#define sz(c) int((c).size())
#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FORS(i,a,b,s) for (int i = (a); i < (b); i=i+(s))
#define FORD(i,a,b) for (int i = int(b)-1; i >= (a); i--)
#define FORIT(i,c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)

#define MAXN 1000000


vll adj[MAXN];

int val(int t, int i){ return 4*t + i; }

void edge(int i, int j){
	adj[i].push_back(j);
}

void assertNot(int i){
	edge(2*i,2*i+1);
}

void implyNot(int i, int j){
	edge(2*i,2*j+1);
	edge(2*j,2*i+1);
}

void imply(int i, int j){
	edge(2*i,2*j);
	edge(2*j,2*i);
}

void clause(int i, int j){
	edge(2*i+1,2*j);
	edge(2*j+1,2*i);
}

bool sett[MAXN];
set<int> justset;

bool dfs(int i){
	if (sett[i^1]) return false;
	if (sett[i]) return true;
	sett[i] = true; justset.insert(i);
	FORIT(j,adj[i]) if (!dfs(*j)) return false;
	return true;
}


int main(){
	int n,m; cin >> n >> m;
	FOR(i,0,MAXN) adj[i].clear();
	FOR(i,0,n) FOR(x,0,4) FOR(y,0,4) if (x != y) implyNot(val(i,x),val(i,y));

	FOR(i,0,m){
		int x,y; char c; cin >> x >> y >> c;
		x--,y--;
		switch (c){
			case 'x':
				clause(val(x,0),val(y,0));
				break;
			case '-':
				clause(val(x,1),val(y,1));
				assertNot(val(x,0));
				assertNot(val(y,0));
				assertNot(val(x,3));
				assertNot(val(y,3));
				break;
			case '+':
				clause(val(x,3),val(y,3));
				assertNot(val(x,0));
				assertNot(val(y,0));
				assertNot(val(x,1));
				assertNot(val(y,1));
				break;
			case '=':
				assertNot(val(x,0));
				assertNot(val(y,0));
				imply(val(x,2),val(y,2));
				imply(val(y,2),val(x,2));

				imply(val(x,3),val(y,1));
				imply(val(y,1),val(x,3));

				imply(val(x,1),val(y,3));
				imply(val(y,3),val(x,1));
				break;
		}	
	}

	// we know it is SAT, so just try to compute the assignement
	FOR(i,0,2*4*n) sett[i] = false;
	FOR(i,0,n) FOR(t,0,4) if (sett[2*val(i,t)] == sett[2*val(i,t)+1]) {
		justset.clear();
		if (!dfs(2*val(i,t))) {
			FORIT(j,justset) sett[*j] = false;
			dfs(2*val(i,t)+1);
		}
	}


	FOR(i,0,n) FOR(t,0,4) if (sett[2*val(i,t)]) switch(t){
		case 0: cout << "x"; break;
		case 1: cout << "-"; break;
		case 2: cout << "="; break;
		case 3: cout << "+"; break;
	}



}
