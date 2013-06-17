#include <iostream>
using namespace std;

template <typename T>
struct max_value {
	static const T value = 0;
};

template <>
struct max_value<int> {
	static const int value = 10000000;
};

template <typename T>
struct _is_pointer {
	static const bool value = false;
	
};

template <typename T>
struct _is_pointer<T *> {
	static const bool value = true;
};

template <int size, typename T>
struct S {
	T* arr;
	S() {
		arr = new T[size];
	}
	~S() {
		delete[] arr;
	}
};

int main() {
	//int ans = max_value<int>::value;
	long long ans = max_value<long long>::value;

	S<20, int> A;
	S<10, char> B;

	cout << ans << endl;
	system("pause");
}