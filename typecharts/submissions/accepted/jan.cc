// [NWERC'18] Type Charts, by Jan Kuipers

#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

vector<set<char>> pos;
vector<vector<int>> conn;
string res;

char flip(char c) {
  if (c=='=') return '=';
  if (c=='+') return '-';
  if (c=='-') return '+';
  return '!';
}

set<int> seen;

bool fill(int n, char c) {
  if (!pos[n].count(c)) return false;
  if (res[n]==c) return true;
  if (seen.count(n)) return false;
  res[n] = c;
  seen.insert(n);
  for (int i : conn[n]) {
    if (!fill(i, flip(c))) return false;
  }
  return true;
}

int main() {
  int N,M;
  cin >> N >> M;
  pos = vector<set<char>>(N, {'+','-', '=', 'x'});
  conn = vector<vector<int>>(N);
  for (int i=0; i<M; i++) {
    int a,b;
    string c;
    cin >> a >> b >> c;
    a--;
    b--;    
    if (c=="+") {
      pos[a].erase('-');
      pos[b].erase('-');
    }
    if (c=="-") {
      pos[a].erase('+');
      pos[b].erase('+');
    }
    if (c=="=" && a!=b) {
      conn[a].push_back(b);
      conn[b].push_back(a);
    }
    if (c!="x") {
      pos[a].erase('x');
      pos[b].erase('x');
    }
    if (a==b) {
      pos[a] = set<char>({c[0]});
    }    
  }
  res = string(N, '?');
  for (int i=0; i<N; i++) {
    if (pos[i].count('x')) {
      res[i] = 'x';
    }
  }
  priority_queue<pair<int,int>> pq;
  for (int i=0; i<N; i++) {
    pq.push(make_pair(-pos[i].size(), i));
  }
  while (!pq.empty()) {
    int i = pq.top().second;
    pq.pop();
    if (res[i] != '?') continue;
    for (char c : {'+','-','='}) {
      seen.clear();
      if (fill(i,c)) break;
    }      
  }
  cout << res << endl;  
  return 0;
}
