#include <iostream>
#include <vector>
using namespace std;

const int maxn = 1e6 + 5;
vector<int> v2is[maxn];
int n;
int v2i[maxn];
int i2v[maxn];
int nMatch;
int vMatchIdx[maxn];

bool try_move(int prev_val) {
	for(int i = vMatchIdx[prev_val] + 1; i < v2is[prev_val].size(); ++i) {
		vMatchIdx[prev_val] = i;

		int item = v2is[prev_val][i];

		if(i2v[item] == 0) {
			i2v[item] = prev_val;
			v2i[prev_val] = item;
			return true;
		}
		else {
			int orig_val = i2v[item];
			if(try_move(orig_val)) {
				i2v[item] = prev_val;
				v2i[prev_val] = item;
				return true;
			}
		}
	}
	return false;
}

bool addMatch(int cur_val) {
	for(int i = 0; i < v2is[cur_val].size(); ++i) {
		vMatchIdx[cur_val] = i;

		int item = v2is[cur_val][i];

		if(i2v[item] == 0) {
			i2v[item] = cur_val;
			v2i[cur_val] = item;
			return true;
		}
		else {
			int orig_val = i2v[item];
			if(try_move(orig_val)) {
				i2v[item] = cur_val;
				v2i[cur_val] = item;
				return true;
			}
		}
	}
	return false;
}

int main() {
	cin >> n;
	for(int i = 1; i <= n; ++i) {
		int val1, val2;
		cin >> val1 >> val2;
		v2is[val1].emplace_back(i);
		v2is[val2].emplace_back(i);
	}

	while(true) {
		if(addMatch(nMatch + 1)) ++nMatch;
		else break;
	}
	cout << nMatch << endl;
	return 0;
}