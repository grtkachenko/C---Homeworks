#include <iostream>
#include "solve.h"
namespace A {
	void f() {};
}

namespace SQR = A;

namespace {
	void f() {};
}

using namespace SQR;
void f() {
}

bool volatile* gg = 0;

int main() {
	volatile bool f = true;
	gg = &f;
	while (f) {}
}
