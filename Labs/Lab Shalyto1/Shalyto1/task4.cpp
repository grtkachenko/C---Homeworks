#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;
const int MAX_N = 1000;
int main() {
	 freopen("start.in", "r", stdin);
	 freopen("start.out", "w", stdout);
	 int m, n;
	 cin >> m >> n;
	 int to[MAX_N][2];
	 char state_char[MAX_N];
	 bool can[MAX_N], help_can[MAX_N];

	 for (int i = 0; i < n; i++) {
			for (int j = 0; j < 2; j++) {
				 scanf("%d", &to[i][j]);
				 to[i][j]--;
			}
			cin >> state_char[i];
			can[i] = true;
			help_can[i] = false;
	 }
	 string target;
	 cin >> target;

	 for (int i = m - 1; i >= 0; i--) {
			for (int j = 0; j < n; j++) {
				  if (state_char[to[j][0]] == target[i] && can[to[j][0]] || state_char[to[j][1]] == target[i] && can[to[j][1]]) {
						  help_can[j] = true;
				  }
			}
			for (int j = 0; j < n; j++) {
				  can[j] = help_can[j];
				  help_can[j] = false;
			}
	 }

	 int total = 0;
	 vector<int> ans;
	 for (int i = 0; i < n; i++) {
			if (can[i]) {
				  total++;
				  ans.push_back(i + 1);
			}
	 }
	 cout << total << " ";
	 for (int i = 0; i < ans.size(); i++) {
		 cout << ans[i] << " ";
	 }
}
