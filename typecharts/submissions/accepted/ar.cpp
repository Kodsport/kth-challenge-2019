// Author Alexander Rass
#include <bits/stdc++.h>
using namespace std;
const int MAXE = 1.1e5;
const int MAXN = 1.1e5;
string result_string;
bool has_types[MAXN][4];
int mark[MAXN];
int get_type(char c){
    if(c == 'x')return 0;
    if(c == '-')return 1;
    if(c == '=')return 2;
    if(c == '+')return 3;
    assert(false);
    return -1;
}
vector<int> adj[MAXN];
bool check_bipartite(int n, vector<int>& p0, vector<int> &p1, int c=-2){
    if(mark[n] != -1)return mark[n] == c;
    p0.push_back(n);
    mark[n] = c;
    bool res = true;
    for(auto to: adj[n])res &= check_bipartite(to, p1,p0,5-c);
    return res;
}
int main(){
    int N,M;
    cin >> N >> M;
    result_string = string(N,' ');
    for(int i = 0; i < N; i++){
        mark[i] = -1;
    }
    memset(has_types,0,sizeof(has_types));
    for(int m = 0; m < M; m++){
        int a,b,c;
        string s;
        cin >> a >> b >> s;
        c = get_type(s[0]);
        has_types[--a][c] = 1;
        has_types[--b][c] = 1;
        if(c == 2){
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
    }
    for(int i = 0; i < N; i++)if(mark[i] == -1){
        if(!has_types[i][1] && !has_types[i][2] && !has_types[i][3]){
            result_string[i] = 'x';
            mark[i] = i;
        } else if(mark[i] == -1){
            vector<int> p0, p1;
            bool bp = check_bipartite(i,p0,p1);
            for(auto it: p0)for(int j = 1; j < 4; j++)has_types[i][j] |= has_types[it][j];
            for(auto it: p1)for(int j = 1; j < 4; j++)has_types[i][4-j] |= has_types[it][j];
            if(!bp || (has_types[i][1] && has_types[i][3])){
                for(auto it: p0)result_string[it] = '=';
                for(auto it: p1)result_string[it] = '=';
            } else if(has_types[i][1]){
                for(auto it: p0)result_string[it] = '-';
                for(auto it: p1)result_string[it] = '+';
            } else {
                for(auto it: p0)result_string[it] = '+';
                for(auto it: p1)result_string[it] = '-';
            }
        }
    }
    cout << result_string << endl;
	return 0;
}
