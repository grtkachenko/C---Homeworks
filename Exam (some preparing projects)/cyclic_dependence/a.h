#pragma once
#include "b.h"

struct A {
	B * x;
	
	void f() {
		x->g();
	}
};

void B::g() {
		y->f();
}