#include <bits/stdc++.h>

const int REPS = 50000000;

int main(void) {
    srand48(2019);
    int n, m;
    scanf("%d%d", &n, &m);
    int src[m], dst[m];
    double prob[m];
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%lf", src+i, dst+i, prob+i);
        --src[i];
        --dst[i];
    }
    int survivals[n], dead[n];
    for (int i = 0; i < n; ++i) {
        survivals[i] = 0;
        dead[i] = -1;
    }

    for (int iter = 0; iter < REPS; ++iter) {
        for (int i = 0; i < m; ++i) {
            if (dead[src[i]] < iter && drand48() < prob[i])
                dead[dst[i]] = iter;
        }
        for (int i = 0; i < n; ++i)
            survivals[i] += dead[i] < iter;
    }
    for (int i = 0; i < n; ++i)
        printf("%.10f\n", 1.0*survivals[i] / REPS);
}
