#include <iostream>
#include <vector>
using namespace std;

const int maxn = 1005;

int n, m, e;
int ans;
int l2r[maxn];
int r2l[maxn];
vector<int> edge[maxn];

/**
 * See whether we can add a match to cur character.
 * */
bool addMatch(int cur) {

}

int main() {
	cin >> n >> m >> e;
	for(int i = 0; i < e; ++i) {
		int u, v;
		cin >> u >> v;
		edge[u].emplace_back(v);
	}

	for(int i = 1; i <= n; ++i) {
		if(addMatch(i))
			++ans;
	}
	cout << ans << endl;
	return 0;
}