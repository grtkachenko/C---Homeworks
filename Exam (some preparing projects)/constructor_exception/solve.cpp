#include <iostream>
using namespace std;

struct A {
	A() {
		cout << "constructor A" << endl;
	}
	~A() {
		cout << "destructor A" << endl;
	}
};
struct B {
	B() {
		cout << "constructor B" << endl;
	}
	~B() {
		cout << "destructor B" << endl;
	}
};

struct C {
	A a;
	B b;
	C() {
		cout << "constructor C" << endl;
		throw 1;
	}
	~C() {
		cout << "destructor C" << endl;
	}
};

struct D {
	A a;
	B b;
	C c;
	D() try : a(), b(), c() { cout << "constructor D" << endl; }
	catch( ... ) {
		cout << "cought" << endl;
	}
	~D() {
		cout << "destructor D" << endl;
	}

};
A foo() {
	A a;
	return a;
}
int main() {
	//A a = foo();
	
	try {
		D d;
	} catch ( ... ) {
	
	}
	system("pause");
}
