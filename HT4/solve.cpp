#include "point.cpp"
#include <stack>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
class convex_hull_builder {
private: 
	static double vector_mul(point &a, point &b, point &c) {
		return ((double)b.x - a.x) * ((double)c.y - b.y) - ((double)b.y - a.y) * ((double)c.x - b.x);
	}
public:
	static vector<point> convex_hull(vector<point> data) {
		int n = data.size();
		sort(data.begin(), data.end());
		for (int i = n - 2; i >= 0; i--) {
			data.push_back(data[i]);
		}
		stack<int> st;
		vector<int> ans;
		for (int i = 0; i < 2 * n - 1; i++) {
			if (st.size() < 2) {
				st.push(i); 
			} else {
				while (st.size() > 1) {
					int p2_num = st.top();
					st.pop();
					int p1_num = st.top();
					if (vector_mul(data[p1_num], data[p2_num], data[i]) > 0) {
						st.push(p2_num);
						break;
					}
				}
				st.push(i);
			}
			if (i == n - 1) {
				ans.resize(st.size());
				int cur_num = st.size() - 1;
				while (!st.empty()) {
					ans[cur_num] = st.top();
					cur_num--;
					st.pop();
				}
				st.push(i);
			}
		}
		ans.resize(ans.size() + st.size() - 1);
		int cur_num = ans.size() - 1;
		while (!st.empty()) {
			if (st.size() != 1) {
				ans[cur_num] = st.top();
			}
			cur_num--;
			st.pop();
		}
	
		vector<point> res(ans.size() - 1);
		for (int i = 0; i < ans.size() - 1; i++) {
			res[i] = data[ans[i]];
		}
		return res;
	}
};