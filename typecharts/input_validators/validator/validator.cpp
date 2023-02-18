#include "validator.h"

void run() {
	int n = Int(1, 100'000);
	Space();
	int m = Int(1, 100'000);
	Endl();

	for (int j = 0; j < m; j++) {
		Int(1, n);
		Space();
		Int(1, n);
		Space();
		char c = Char();
		assert(c == '-' || c == '+' || c == '=' || c == 'x');
		Endl();
	}
}
