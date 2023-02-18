#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll solve(ll L, ll N){
    if(L%N == 0)return 1;
    return 1 + solve(L, N-L%N);
}

int main() {
    ll N,L;
    cin >> L >> N;
    cout << solve(L,N) << "\n";
    return 0;
}

