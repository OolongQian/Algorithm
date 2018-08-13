#include <iostream>
#include <queue>
#include <cstring>
// #define _DEBUG
using namespace std;

const int maxState = 5e6;
const int LEN = 9;
const int EDGE = 3;
int factorial[10];

inline int Cantor(int a[], int len) {
	static int small[10];		/// 表示在之后的数字当中比num[i]小的数的数量。
	for(int i = 0; i < len; ++i) {
		small[i] = 0;
		for(int j = i + 1; j < len; ++j) {
			if(a[j] < a[i])
				++small[i];
		}
	}

//	for(int i = 0; i < len; ++i) {
//		cout << small[i] << ' ';
//	}
//	cout << endl;

	int ans = 0;
	for(int i = 0; i < len; ++i) {
		ans += small[i] * factorial[len - 1 - i];
	}
	return ans;
}

void unCantor(int c, int a[], int len) {
	static int small[10];
	static bool unUse[10];
	for(int i = 0; i < len; ++i) unUse[i] = true;

	for(int i = 0; i < len; ++i) {
		small[i] = c / factorial[len - 1 - i];
		c = c % factorial[len - 1 - i];
	}

//	for(int i = 0; i < len; ++i)
//		cout << small[i] << ' ';
//	cout << endl;

	for(int i = 0; i < len; ++i) {
		int cur, count = 0;
		for(cur = 0; cur < len; ++cur) {
			if(unUse[cur])
				++count;
			if(count == small[i] + 1) {
				a[i] = cur;
				unUse[cur] = false;
				break;
			}
		}
	}

//	for(int i = 0; i < len; ++i)
//		cout << a[i] << ' ';
//	cout << endl;

}

inline int getDist(int a, int b) {
	return (abs(a / 3 - b / 3) + abs(a % 3 - b % 3));
}

inline int guess(int cantor) {
	static int target[] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
	static int state[10];

	unCantor(cantor, state, LEN);
	int dist = 0;
	for(int i = 0; i < LEN; ++i) {
		dist += getDist(state[i], target[i]);
	}
	return dist;
}

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

struct node {
	int status;
	int dist;
	int guess;
	node (int a = -1, int b = -1, int c = -1) {
		status = a;
		dist = b;
		guess = c;
	}
	bool operator< (const node &other) const {
		if(dist + guess != other.dist + other.guess)
			return dist + guess > other.dist + other.guess;
		else
			return dist > other.dist;
	}
};

inline int co2idx(int x, int y) {
	return x * EDGE + y;
}

inline void idx2co(int idx, int &x, int &y) {
	x = idx / EDGE;
	y = idx % EDGE;
}

void find_nei(int status, vector<int> &v) {
	static int arr_states[10];
	unCantor(status, arr_states, LEN);
	v.clear();

	int zero_idx, zero_x, zero_y;
	for(zero_idx = 0; zero_idx < LEN; ++zero_idx) {
		if(arr_states[zero_idx] == 0)
			break;
	}

	idx2co(zero_idx, zero_x, zero_y);
	if(zero_x != EDGE - 1) {
		swap(arr_states[zero_idx], arr_states[zero_idx + EDGE]);
		v.push_back(Cantor(arr_states, LEN));
		swap(arr_states[zero_idx], arr_states[zero_idx + EDGE]);
	}
	if(zero_x != 0) {
		swap(arr_states[zero_idx], arr_states[zero_idx - EDGE]);
		v.push_back(Cantor(arr_states, LEN));
		swap(arr_states[zero_idx], arr_states[zero_idx - EDGE]);
	}
	if(zero_y != EDGE - 1) {
		swap(arr_states[zero_idx], arr_states[zero_idx + 1]);
		v.push_back(Cantor(arr_states, LEN));
		swap(arr_states[zero_idx], arr_states[zero_idx + 1]);
	}
	if(zero_y != 0) {
		swap(arr_states[zero_idx], arr_states[zero_idx - 1]);
		v.push_back(Cantor(arr_states, LEN));
		swap(arr_states[zero_idx], arr_states[zero_idx - 1]);
	}
}

void execute() {
	static int target[] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
	static int target_status;
//	openList.emplace(1, 1, 1);
//	openList.emplace(1, 3, 2);
//	auto top = openList.top();
//	cout << top.guess << ' ' << top.status << endl;

	static bool closeList[maxState];
	static int tmp_state[LEN];


	memset(closeList, false, sizeof(closeList));
	target_status = Cantor(target, LEN);

	int start[10];
	for(int i = 0; i < 9; ++i) {
		cin >> start[i];
	}

	priority_queue<node> openList;
	node beg;
	beg.status = Cantor(start, LEN);
	beg.dist = 0;
	beg.guess = guess(beg.status);
	openList.push(beg);

	while(!openList.empty()) {
		auto front = openList.top();
		openList.pop();
		if(front.status == target_status) {
			printf("%d\n", front.dist);
			return;
		}
		if(closeList[front.status]) continue;

		closeList[front.status] = true;
		unCantor(front.status, tmp_state, LEN);

		vector<int> nei_status;
		find_nei(front.status, nei_status);

#ifdef _DEBUG
		printf("current state: \n");
		for(int i = 0; i < EDGE; ++i) {
			for(int j = 0; j < EDGE; ++j) {
				printf("%d ", tmp_state[i * EDGE + j]);
			}
			printf("\n");
		}
		printf("\n");

		printf("neighbouring state: \n");
		int tmp_nei_state[10];
		int k = 0;
		for(auto nei : nei_status) {
			++k;
			unCantor(nei, tmp_nei_state, LEN);
			printf("nei %d: \n", k);
			for(int i = 0; i < EDGE; ++i) {
				for(int j = 0; j < EDGE; ++j) {
					printf("%d ", tmp_nei_state[i * EDGE + j]);
				}
				printf("\n");
			}
			printf("\n");
		}

#endif
		for(auto nei : nei_status) {
			if(closeList[nei])
				continue;
			node neighb;
			neighb.status = nei;
			neighb.dist = front.dist + 1;
			neighb.guess = guess(neighb.status);
			openList.push(neighb);
		}
	}
	printf("No Solution!\n");
}

int main() {
	int t;

	factorial[0] = 1;
	for(int i = 1; i <= 9; ++i) {
		factorial[i] = factorial[i - 1] * i;
	}

//	int num[] = {1, 2, 3};
//	cout << Cantor(num, 3) << endl;
//	unCantor(1, num, 3);
	cin >> t;
	while(t--) {
		execute();
	}

	return 0;
}
