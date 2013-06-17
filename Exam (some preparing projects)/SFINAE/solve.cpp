#include <iostream>
using namespace std;
//typename T::inner_type



template <typename T> 
void f(T a, T b) {
	cout << "1" << endl;
}

template <typename T>
void f(T * a, T * b) {
	cout << "2" << endl;
}

template <>
void f<int *>(int * a, int * b) {
	cout << "3" << endl;
}



template <bool cond> 
struct _enable_if {};

template <> 
struct _enable_if<true> {
	typedef void const * type;
};

template <typename T>
struct _is_integral {
	static const bool value = false;
};

template <>
struct _is_integral<int> {
	static const bool value = true;
};


//template <typename T> 
//void f<is_integral<T>::value>::type {
//};
//
//template <typename T> 
//void f<!is_integral<T>::value>::type {
//};

int main() {
	int a, b;

	f(&a, &b);
	/*if (is_integral<double>::value) {
		cout << "is_integral" << endl;
	} else {
		cout << "not_is_integral" << endl;
	}*/
	system("pause");
}