#include <iostream>
using namespace std;

template <int size>
struct fact {
	static const int ans = fact<size - 1>::ans * size; 
};

template <>
struct fact<0> {
	static const int ans = 1; 
};

struct empty {
};

template <typename Data, typename Next>
struct node {
	typedef Data data;
	typedef Next next;
};

template <typename List, int i>
struct at {
	typedef typename at<typename List::next, i - 1>::result result;
};

template <typename List>
struct at<typename List, 0> {
	typedef typename List::data result;
};


int main() {
	int ans = fact<5>::ans;
	cout << ans << endl;

	typedef node<int, node<long long, node<char, empty>>> list; 
	cout << sizeof(at<list, 2>::result) << endl;
	system("pause");
}
