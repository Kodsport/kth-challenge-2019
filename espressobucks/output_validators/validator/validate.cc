#include <vector>
#include <string>
#include "validate.h"

using namespace std;

// Reads a grid of specified size from an input stream and checks
// formatting (that it has the correct dimensions and consists only of
// '#', '.' and 'E')
//
// Throughout the validator, grids are always padded with a frame of
// '#'s [so have size (n+2)x(m+2)].
vector<string> read_grid(int n, int m, istream &in, feedback_function feedback) {
    vector<string> grid(n+2, string(m+2, '#'));
    for (int i = 1; i <= n; ++i) {
        string row;
        if (!(in >> row)) {
            feedback("failed to read row %d/%d of grid", i, n);
        }
        if (row.length() != m) {
            feedback("row %d of grid has incorrect length %d instead of %d", row.length(), m);
        }
        grid[i] = '#' + row + '#';
        for (int j = 1; j <= m; ++j) {
            char c = grid[i][j];
            if (c != '.' && c != '#' && c != 'E' && c != 'e') {
                feedback("Row %d col %d of grid has invalid character ascii %d ('%c')",
                         i, j, c, c);
            }
            if (c == 'e') grid[i][j] = 'E';
        }
    }
    return grid;
}

// Check that sol is a correct solution
// Assumes sol has correct dimensions and consists only of '#', '.' and 'E'
void check_solution(int n, int m,
                    const vector<string> &input,
                    const vector<string> &sol,
                    feedback_function feedback) {
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            if (input[i][j] == '#') {
                if (sol[i][j] != '#') {
                    feedback("Water cell %d %d changed into '%c'", i, j, sol[i][j]);
                }
            } else { // input[i][j] == '.'
                if (sol[i][j] == '#') {
                    feedback("Land cell %d %d changed into '%c'", i, j, sol[i][j]);
                }
                bool hasSelf = (sol[i][j] == 'E');
                bool hasNeigh = (sol[i-1][j] == 'E' ||
                                 sol[i+1][j] == 'E' ||
                                 sol[i][j-1] == 'E' ||
                                 sol[i][j+1] == 'E');
                if (!hasSelf && !hasNeigh) {
                    feedback("Land cell %d %d does not have any neighboring Espresso", i, j);
                }
                if (hasSelf && hasNeigh) {
                    feedback("Land cell %d %d has an Espresso and is also adjacent to one", i, j);
                }
            }
        }
}

int main(int argc, char **argv) {
    init_io(argc, argv);

    int n, m;
    judge_in >> n >> m;
    vector<string> input = read_grid(n, m, judge_in, judge_error);
    vector<string> output = read_grid(n, m, cin, wrong_answer);
    check_solution(n, m, input, output, wrong_answer);

    // Ignore judge_ans -- there is always a solution and no objective
    // function to optimize, so very little value in reading ans file
    // and checking that it is correct.

    string trailing;
    if (judge_in >> trailing) {
        wrong_answer("Trailing output");
    }

    accept();
}
