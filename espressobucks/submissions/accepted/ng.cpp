#include <bits/stdc++.h>
using namespace std;

int n,m;
string grid[101];
vector<pair<int,int> > cells;
int DX[4] = {0,0,1,-1};
int DY[4] = {1,-1,0,0};

bool inbounds(int i, int j){
    return i >= 0 && j >= 0 && i < n && j < m;
}

int main() {
    cin >> n >> m;
    for(int c1 = 0; c1 < n; c1++){
        cin >> grid[c1];
        for(int c2 = 0; c2 < m; c2++){
            cells.push_back({c1,c2});
        }
    }

    random_shuffle(cells.begin(), cells.end());
    bool only_water = 1;
    for(int c1 = 0; c1 < n*m; c1++){
        int x = cells[c1].first;
        int y = cells[c1].second;
        if(grid[x][y] == '.'){
            only_water = 0;
            bool covered = 0;
            for(int c2 = 0; c2 < 4; c2++){
                if(inbounds(x+DX[c2], y+DY[c2])){
                    if(grid[x+DX[c2]][y+DY[c2]] == 'E')covered = 1;
                }
            }
            if(!covered){
                grid[x][y] = 'E';
            }
        }
    }

    assert(!only_water);

    for(int c1 = 0; c1 < n; c1++){
        cout << grid[c1] << "\n";
    }

    return 0;
}
