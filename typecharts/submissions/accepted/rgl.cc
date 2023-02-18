#include <bits/stdc++.h>
using namespace std;

enum Variable:int{zero,half,one,two};
const char *str="x-=+";

#define MAXN 100000
#define MAXV (4*(MAXN))

set<int> edge[MAXV];
int half_of(int x){return x*4+0;}
int two_of(int x){return x*4+2;}
void imply(int a,int b) {edge[a].insert(b);}
void either(int a,int b) {imply(a^1,b); imply(b^1,a);}
void equal(int a,int b) {imply(a,b); imply(b,a); imply(a^1,b^1); imply(b^1,a^1);}
void never(int a) {imply(a,a^1);}

int indices=0;
int idex[MAXV];
int root[MAXV];
bool instack[MAXV];
stack<int> s;

void strong(int x){
  idex[x]=root[x]=++indices;
  s.push(x); instack[x]=true;
  for (int y: edge[x]){
    if (idex[y]==0){
      strong(y);
      root[x]=min(root[x],root[y]);
    }else if (instack[y]){
      root[x]=min(root[x],idex[y]);
    }
  }
  if (root[x]==idex[x]){
    while (instack[x]){
      int y=s.top(); s.pop(); instack[y]=false;
      root[y]=idex[x];
    }
  }
}

int main(){
  int n,m; cin>>n>>m;
  vector<bool> zeroed(n,true);

  for (int i=n; i--;){
    either(half_of(i)^1,two_of(i)^1);
  }
  while (m--){
    int a,b; string c; cin>>a>>b>>c; --a,--b;
    Variable v=(c[0]=='+'?two:c[0]=='='?one:c[0]=='-'?half:zero);
    if (v!=zero){
      zeroed[a]=zeroed[b]=false;
      switch (v){
        case half:{
          either(half_of(a),half_of(b));
          never(two_of(a));
          never(two_of(b));
          break;
        }
        case one:{
          equal(half_of(a),two_of(b));
          equal(half_of(b),two_of(a));
          break;
        }
        case two:{
          either(two_of(a),two_of(b));
          never(half_of(a));
          never(half_of(b));
        }
      }
    }
  }

  vector<bool> values(n*4+1);
  vector<int> deps(n*4+1);
  vector<int> visited(n*4);

  for (int i=0; i<n*4; i++)
    if (idex[i]==0)
      strong(i);
  for (int i=0; i<n*4; i++)
    if (root[i]==root[i^1]){
      cout<<"impossible"<<endl;
      return 0;
    }
  for (int i=0; i<n*4; i++)
    for (int j: edge[i])
      if (not zeroed[i/4] and root[i]!=root[j])
        deps[root[j]]++;
  deque<int> todo;
  for (int i=0; i<n*4; i++)
    if (idex[i]==root[i] and deps[idex[i]]==0)
      todo.push_back(i), visited[i]=true;
  while (not todo.empty()){
    int x=todo.front(); todo.pop_front();
    values[root[x^1]]=not values[root[x]];
    for (int y: edge[x])
      if (root[y]==root[x]){
        if (not visited[y]) {visited[y]=true;todo.push_front(y);}
      }else{
        if (values[root[x]]) values[root[y]]=true;
        if (not --deps[root[y]]) {visited[y]=true;todo.push_back(y);}
      }
  }

  for (int i=0; i<n; i++)
    if (zeroed[i])
      cout<<str[(int)zero];
    else if (values[root[half_of(i)]])
      cout<<str[(int)half];
    else if (values[root[two_of(i)]])
      cout<<str[(int)two];
    else
      cout<<str[(int)one];
  cout<<endl;
}
