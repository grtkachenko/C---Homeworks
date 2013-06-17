#include <iostream>
#include <vector>
using namespace std;

struct A {
	static const int x = 3;	
};

void f(int a) {
	cout << 1 << endl;
};


void f(long long a) {
	cout << 2 << endl;
};

void f(double a) {
	cout << 3 << endl;
};

inline void f() {
}
int hours = 1;
extern void foo();

extern "C" {
	int g(int a) {
		return 1;
	}
}

template <typename T> 
void f(T a) {
}

template <> 
void f<int>(int a) {
}


int main() {
	foo();
	cout << hours << endl;
	int x = A::x;
	int * const p = &x;
	int * p1 = p;
	system("pause");
	return 0;
}