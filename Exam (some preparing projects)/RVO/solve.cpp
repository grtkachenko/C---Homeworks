#include <iostream>
using namespace std;

namespace A
{
	void f()
	{
	}
}
namespace B
{
	void f()
	{
	}
}

namespace C
{
	namespace D = A;
	namespace D = B;
}

struct T
{
	T(int)
	{}

	T& operator=(int)
	{
		return *this;
	}
};

int main()
{
	T a = 5;
}
