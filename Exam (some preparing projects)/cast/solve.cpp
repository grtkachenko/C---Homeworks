#include <iostream>
using namespace std;
void pr(int x) {
	cout << x << endl; 
}

struct A {
	int x;
	A() : x(1) {
	}
	virtual void f() {
		pr(x);
	}
	
};

struct B : public A {
	virtual void f() {
		pr(x);
	}
};

struct C {
	virtual void f() {
		pr(x);
	}
	int x;
	C() : x(2) {
	}
};

struct D : public C {
	virtual void f() {
		pr(x);
	}
	int y;
	D() : y(3) {
	}
};

int main() {
	A a;
	A * pa;
	B b;
	B * pb;
	C c;
	C * pc;
	D d;
	D * pd;
	//dynamic
	//1
	pb = dynamic_cast<B*>(&a);
	if (pb != nullptr) {
		pb->f();
	} else {
		cout << "null" << endl;
	}

	//2
	pa = dynamic_cast<A*>(&b);
	if (pa != nullptr) {
		pa->f();
	} else {
		cout << "null" << endl;
	}	

	//3 CE, если нет виртульаных функции
	//static
	//1
	pb = static_cast<B*>(&a);
	if (pb != nullptr) {
		pb->f();
	} else {
		cout << "null" << endl;
	}

	//2
	pa = static_cast<A*>(&b);
	if (pa != nullptr) {
		pa->f();
	} else {
		cout << "null" << endl;
	}	
	
	//3
	pd = static_cast<D*>(&c);
	if (pd != nullptr) {
		pd->f();
		pr(pd->y);
	} else {
		cout << "null" << endl;
	}

	//4 CE
	//pd = static_cast<D*>(&b);

	//const_cast
	A const aa;
	A& aaa = const_cast<A&>(aa);
	//aa.x = 1; - error
	aaa.x = 1;

	A * aa1 = new A();
	A const * aaa1 = aa1;
	
	//reinterpret_cast
	pd = reinterpret_cast<D*>(&b);

	system("pause");
}
