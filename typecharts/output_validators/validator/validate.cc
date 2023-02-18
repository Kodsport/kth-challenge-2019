#include <vector>
#include <tuple>
#include <cstring>
#include "validate.h"

using namespace std;

// Whether "impossible" answers should be allowed to occur
#define SUPPORT_IMPOSSIBLE

struct Rel {
	int a, b;
	char c;
};

pair<int, vector<Rel>> read_input(istream &in) {
    int n, m;
    in >> n >> m;
    vector<Rel> rels(m);
    for (auto &v: rels) {
        in >> v.a >> v.b >> v.c;
		--v.a, --v.b;
		assert(0 <= v.a && v.a < n);
		assert(0 <= v.b && v.b < n);
		assert(v.c == '+' || v.c == '-' || v.c == '=' || v.c == 'x');
    }
    return {n, rels};
}

string read_solution(int n, istream &sol, feedback_function feedback) {
	string s, tmp;
	if (!(sol >> s)) return "";
	if (sol >> tmp) feedback("Trailing output");
	for (char &c : s) {
		c = (char)tolower(c);
	}
	return s;
}

void check_solution(int n, const vector<Rel> &rels, const string &sol, feedback_function feedback) {
	if ((int)sol.size() != n) {
		feedback("Wrong string length (%d, should be %d)", (int)sol.size(), n);
	}
	for (char c : sol) {
		if (c != '+' && c != '-' && c != '=' && c != 'x') {
			feedback("String contains invalid character \"%c\" (should consist only of +-=x)", c);
		}
	}

	for (Rel rel : rels) {
		char a = sol[rel.a], b = sol[rel.b];
		char out;
		if (a == 'x' || b == 'x') out = 'x';
		else if (a == '=') out = b;
		else if (b == '=') out = a;
		else if (a == b) out = a;
		else out = '=';
		if (out != rel.c) {
			feedback("Attack (%d, %d) gave %c, but %c was expected", rel.a+1, rel.b+1, out, rel.c);
		}
	}
}

int main(int argc, char **argv) {
    init_io(argc, argv);

    int n;
    vector<Rel> rels;
    tie(n, rels) = read_input(judge_in);
    string out = read_solution(n, cin, wrong_answer);
    string ans = read_solution(n, judge_ans, judge_error);

#ifdef SUPPORT_IMPOSSIBLE
	if (out == "impossible") {
		if (ans != "impossible") {
			check_solution(n, rels, ans, judge_error);
            wrong_answer("'impossible' claimed, but there is a solution");
		}
		accept();
	} else if (ans == "impossible") {
		check_solution(n, rels, out, wrong_answer);
		judge_error("judge answer says 'impossible', but submission found a valid solution");
	}
#endif

	check_solution(n, rels, ans, judge_error);
	check_solution(n, rels, out, wrong_answer);
    accept();
}
