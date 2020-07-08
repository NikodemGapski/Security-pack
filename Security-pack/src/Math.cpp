#include "Math.h"

namespace Math {
	int Power(int base, int power) {
		int output = 1;
		for (int i = 0; i < power; i++) {
			output *= base;
		}
		return output;
	}

	int Power(int base, int power, int modulo) {
		_int64 output = 1;
		for (int i = 0; i < power; i++) {
			output *= base;
			output %= modulo;
		}
		return (int)output;
	}
}
