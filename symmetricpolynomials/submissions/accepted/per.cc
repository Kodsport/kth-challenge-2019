#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const double EPS = 1e-9; // FIXME figure out what value of eps works
typedef vector<double> poly;

poly read() {
    int n;
    scanf("%d", &n);
    poly ret(n+1);
    for (int i = n; i >= 0; --i) scanf("%lf", &ret[i]);
    return ret;
}

ll binom(int n, int k) {
    ll r = 1;
    for (int i = 0; i < k; ++i)
        r = r*(n-i)/(i+1);
    return r;
}

int main(void) {
    poly X = read();
    poly Y = read();

    int d = max(X.size(), Y.size()) - 1;
    X.resize(d+1);
    Y.resize(d+1);

    if (d == 0) {
        if (X[0] != 0 || Y[0] != 0)
            printf("%lf %lf %lf\n", -Y[0], X[0], 0.0);
        else
            printf("1 0 0\n");
    } else if (d == 1) {
        printf("%lf %lf %lf\n", X[1], Y[1], 0.0);
    } else {
        double C, S;
        if (d % 2) {
            C = -Y[d];
            S = X[d];
        } else {
            C = X[d];
            S = Y[d];
        }
        for (int i = 0; i <= d; ++i) {
            double tmp = C*X[i] + S*Y[i];
            Y[i] = -S*X[i] + C*Y[i];
            X[i] = tmp;
        }

        double t0;
        if (d % 2)
            t0 = -Y[d-1] / (d*Y[d]);
        else
            t0 = -X[d-1] / (d*X[d]);

        for (int i = 1; i <= d; ++i) {
            const poly &P = (i % 2 ? X : Y);
            double coeff(0), t0_pow(1);
            for (int k = i; k <= d; ++k) {
                coeff = coeff + binom(k, i)*P[k]*t0_pow;
                t0_pow = t0_pow * t0;
            }
            if (fabs(coeff) > EPS) {
                printf("0 0 0\n");
                return 0;
            }
        }

        double coeff = 0, t0_pow = 1;
        for (int k = 0; k <= d; ++k) {
            coeff = coeff + Y[k]*t0_pow;
            t0_pow = t0_pow * t0;
        }

        printf("%lf %lf %lf\n", -S, C, -coeff);
    }
}
