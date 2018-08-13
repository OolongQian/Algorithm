#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int factor[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};
vector<int> statnum(9);
vector<int> des({1, 2, 3, 4, 5, 6, 7, 8, 9});
int destination;

struct state {
	int f, g, h, x;
	state(int f, int g, int h, int x):f(f), g(g), h(h), x(x){};
	friend bool operator<(const state &a, const state &b) {
		if(a.f != b.f) return a.f > b.f;
		else return a.g > b.g;  /// !!!!!!!!!!!!!!!!
	}
};

int cantor(const vector<int>& num) {
	int x = 0;
	for(int i = 0; i < 9; ++i) {
		int tp = 0;
		for(int j = i + 1; j < 9; ++j) {
			if(num[i] > num[j])
				tp++;
		}
		x += tp * factor[8 - i];
	}
	return x;
}

vector<int> decantor(int x) {
	vector<int> num;
	int a[9] = {0};
	int used[9] = {false};
	for(int i = 0; i < 9; ++i) {
		a[i] = x / factor[8 - i];
		x %= factor[8 - i];

		int cnt = 0;
		for(int j = 0; j < 9; ++j) {
			if(!used[j]) {
				cnt++;
				if(a[i] + 1 == cnt) {
					num.push_back(j + 1);
					used[j] = 1;
					break;
				}
			}
		}
	}
	return num;
}

int getDist(int a, int b) {
	return (abs(a / 3 - b / 3) + abs(a % 3 - b % 3));
}

int getEvaluation(vector<int> num) {
	int h = 0;
	for(int i = 0; i < 9; ++i) {
		h += getDist(i, num[i] - 1);
	}
	return h;
}

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

inline void idx2co(int idx, int &x, int &y) {
	x = idx / 3;
	y = idx % 3;
}

void find_nei(int status, vector<int> &v) {
	vector<int> curstate = decantor(status);
	v.clear();

	int zero_idx, zero_x, zero_y;
	for(zero_idx = 0; zero_idx < 9; ++zero_idx) {
		if(curstate[zero_idx] == 9)
			break;
	}

	idx2co(zero_idx, zero_x, zero_y);
	if(zero_x != 3 - 1) {
		swap(curstate[zero_idx], curstate[zero_idx + 3]);
		v.push_back(cantor(curstate));
		swap(curstate[zero_idx], curstate[zero_idx + 3]);
	}
	if(zero_x != 0) {
		swap(curstate[zero_idx], curstate[zero_idx - 3]);
		v.push_back(cantor(curstate));
		swap(curstate[zero_idx], curstate[zero_idx - 3]);
	}
	if(zero_y != 3 - 1) {
		swap(curstate[zero_idx], curstate[zero_idx + 1]);
		v.push_back(cantor(curstate));
		swap(curstate[zero_idx], curstate[zero_idx + 1]);
	}
	if(zero_y != 0) {
		swap(curstate[zero_idx], curstate[zero_idx - 1]);
		v.push_back(cantor(curstate));
		swap(curstate[zero_idx], curstate[zero_idx - 1]);
	}
}

void solve() {
	priority_queue<state> openList;
	static bool vis[5000000];
	memset(vis, false, sizeof(vis));
	int h = getEvaluation(statnum);
	openList.push(state(h, 0, h, cantor(statnum)));
	int step = 0;
	bool hasSolution = false;

	while(!openList.empty()) {
		state cur = openList.top();
		openList.pop();
		int x = cur.x;
		vis[x] = true;

		if(destination == x) {
			hasSolution = true;
			step = cur.g;
			break;
		}

		vector<int> nei_state_cantor;

		find_nei(x, nei_state_cantor);
		for(auto nei : nei_state_cantor) {
			int g = cur.g + 1;
			int h = getEvaluation(decantor(nei));
			int f = g + h;

			if(!vis[nei]) {
				openList.push(state(f, g, h, nei));
			}
		}
	}

	if(!hasSolution) cout << "-1" << endl;
	else cout << step << endl;
}

int main() {
	destination = cantor(des);

	for (int i = 0; i < 9; ++i) {
		cin >> statnum[i];
		if (statnum[i] == 0) statnum[i] = 9;
	}
	solve();
	return 0;
}