#include "set.h"
#include <iostream>
#include <crtdbg.h>



using namespace std;
int main() {
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
	tree_set<int> ts;

	ts.insert(1);
	ts.insert(3);
	ts.insert(3);
	ts.insert(4);
	ts.insert(6);
	ts.insert(7);
	ts.insert(9);

	ts.erase(3);
	ts.erase(7);

	int num = 0;
	for (tree_set<int>::reverse_iterator it = ts.rbegin(); it != ts.rend(); it++) {
		cout << (*it) << endl;
	}
	for (tree_set<int>::iterator it = ts.begin(); it != ts.end(); it++) {
		cout << (*it) << endl;
	}


	system("pause");
}