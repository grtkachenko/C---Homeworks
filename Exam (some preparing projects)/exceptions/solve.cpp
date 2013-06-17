#include <iostream>
struct base
{
	virtual char const* msg()
	{
		return "base";
	}
};

struct derived : base
{
	char const* msg()
	{
		return "derived";
	}
};

static void f() {
	
}
int main() {
	//base * e = new derived();
	try {
		try {
			throw derived();
		} catch (base &e) {
			std::cout << e.msg() << std::endl;
			throw e;
		}
	} catch (base &e) {
		std::cout << e.msg() << std::endl;
	}
	system("pause");
}