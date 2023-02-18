#include <vector>
#include <cmath>
#include "validate.h"

using namespace std;

typedef long double real;
typedef long long int64;
typedef vector<int64> poly;

const real ANGLE_EPS = 1e-6;
const real C_EPS = 1e-6;
const real MAX_COEFF = 1e100;
const real MIN_MAX_COEFF = 0.5;
const real pi = 2.0*acosl(0.0);



pair<poly, poly> read_input(istream &in) {
    int n;
    in >> n;
    poly x(n+1);
    for (int i = n; i >= 0; --i)
        in >> x[i];
    in >> n;
    poly y(n+1);
    for (int i = n; i >= 0; --i)
        in >> y[i];
    return make_pair(x, y);
}


bool is_zero(const vector<real> &L) {
    return L[0] == 0 && L[1] == 0 && L[2] == 0;
}

// Reads a claimed solution (and checks formatting of the input stream)
vector<real> read_solution(istream &sol, feedback_function feedback) {
    real A, B, C;
    if (!(sol >> A >> B >> C)) {
        feedback("Failed to read three double values");
    }
    if (isnanl(A) || isnanl(B) || isnanl(C)) {
        feedback("Nan values");
    }
    if (fabs(A) > MAX_COEFF || fabsl(B) > MAX_COEFF || fabsl(C) > MAX_COEFF) {
        feedback("Too large coefficients (> %Le)", MAX_COEFF);
    }
    if ((A != 0 || B != 0 || C != 0) && fabsl(A) < MIN_MAX_COEFF && fabsl(B) < MIN_MAX_COEFF) {
        feedback("Too small A and B (both < %.1Lf) in a non-zero answer", MIN_MAX_COEFF);
    }
    string tok;
    if (sol >> tok) {
        feedback("Trailing output");
    }
    return vector<real>({A, B, C});
}

// Check difference between two angles mod 2*pi
real compare_directions(real theta1, real theta2) {
    theta1 = fmodl(theta1, 2*pi);
    theta2 = fmodl(theta2, 2*pi);
    real res = 2*pi;
    for (int i = -1; i <= 1; ++i)
        res = min(res, fabsl(theta1 - theta2 + i*2*pi));
    return res;
}

void compare_lines(real A1, real B1, real C1,
                   real A2, real B2, real C2,
                   feedback_function feedback) {
    real theta1 = atan2l(-B1, A1);
    real theta2 = atan2l(-B2, A2);
    real angle_diff = compare_directions(theta1, theta2);

    // Normal of second line pointing in opposite direction, flip to point in the same direction
    if (angle_diff > pi/2) {
        A2 = -A2;
        B2 = -B2;
        C2 = -C2;
        angle_diff = pi - angle_diff;
    }
    if (angle_diff > ANGLE_EPS) {
        feedback("Angles are too different:\nJudge: %.9Lf\n User: %.9Lf\n Diff: %.9Lf\n",
                 theta1, theta2, angle_diff);
    }

    real scale1 = max(fabsl(A1), fabsl(B1));
    real scale2 = max(fabsl(A2), fabsl(B2));

    double C_err = fabs(C1/scale1 - C2/scale2);
    if (C_err > C_EPS*max((real)1.0, fabsl(C1/scale1))) {
        feedback("Value of C is wrong:\nJudge (after scaling): %.9Le\n User (after scaling): %.9Le\nError: %.9Le\n", C1/scale1, C2/scale2, C_err/max((real)1.0, fabsl(C1/scale1)));
    }
}

// If the polynomial is constant, any line through the point works
void check_constant(int64 x, int64 y,
                    real A, real B, real C,
                    feedback_function feedback) {
    real scale = max(fabsl(A), fabsl(B));
    real correct_C = -(A*x + B*y);

    if (fabsl(C - correct_C) > C_EPS*max(scale, correct_C)) {
        feedback("Value of C is wrong:\nCorrect value for the given A and B: %.9Le\n User: %.9Le\nError after scaling by max(|A|, |B|): %.9Le\n", correct_C, C, fabsl(C - correct_C)/scale);
    }
}

// If the polynomial is linear any line perpendicular to the
// polynomial is a valid solution.
void check_linear(poly X, poly Y,
                  real A, real B, real C,
                  feedback_function feedback) {
    // Direction of the polynomial
    real theta_poly = atan2l(Y.size() == 1 ? 0 : Y[1], X.size() == 1 ? 0 : X[1]);
    real theta_normal = atan2l(B, A);
    real angle_diff = compare_directions(theta_poly, theta_normal);

    // angle must be the same or differ by pi
    angle_diff = min(angle_diff, pi - angle_diff);

    if (angle_diff < ANGLE_EPS) {
        // Line is perpendicular to to poly -> any value of C works, nothing more to check
    } else {
        feedback("Bad direction: the provided line is not perpendicular to the polynomial\nDirection of poly: %.9Lf\nNormal vector of line: %.9Lf (diff poly vs normal vector of line %.9Lf)\n",
                 theta_poly, theta_normal, angle_diff);
    }
}


int main(int argc, char **argv) {
    init_io(argc, argv);

    pair<poly, poly> data = read_input(judge_in);
    vector<real> Out = read_solution(cin, wrong_answer);
    vector<real> Ans = read_solution(judge_ans, judge_error);

    int d = (int)max(data.first.size(), data.second.size()) - 1;

    if (is_zero(Ans) != is_zero(Out)) {
        if (is_zero(Ans))
            wrong_answer("User produced a line but there is no solution");
        else
            wrong_answer("User claimed no solution but there is a solution");
    }

    switch (d) {
    case 0:
        check_constant(data.first[0], data.second[0],
                       Ans[0], Ans[1], Ans[2],
                       judge_error);
        check_constant(data.first[0], data.second[0],
                       Out[0], Out[1], Out[2],
                       wrong_answer);
        break;
    case 1:
        check_linear(data.first, data.second,
                     Ans[0], Ans[1], Ans[2],
                     judge_error);
        check_linear(data.first, data.second,
                     Out[0], Out[1], Out[2],
                     wrong_answer);
        break;
    default:
        compare_lines(Ans[0], Ans[1], Ans[2],
                      Out[0], Out[1], Out[2],
                      wrong_answer);
    }

    accept();
}
