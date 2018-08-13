#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int maxn = 1005;

int n, m, e;
int ans;
int l2r[maxn];
int r2l[maxn];
bool edge[maxn][maxn];
int loveIdx[maxn];

/**
 * See whether we can find another love for lft.
 * If true, turn it.
 * */
bool teng(int lft) {
	/// find current lover's index.
	int lv_idx = loveIdx[lft];

	for (int i = lv_idx + 1; i <= m; ++i) {
		loveIdx[lft] = i;
		if (edge[lft][i]) {
			int love = i;

			if (r2l[love] == 0 || teng(r2l[love])) {
				l2r[lft] = love;
				r2l[love] = lft;
				return true;
			}
		}
	}
	return false;
}

/**
 * See whether we can add a match to cur character.
 * */
bool addMatch(int cur) {
	for(int i = 1; i <= m; ++i) {
		loveIdx[cur] = i;
		if(edge[cur][i]) {
			int love = i;
			if(r2l[love] == 0) {
				r2l[love] = cur;
				l2r[cur] = love;
				return true;
			}
			else {
				int lft = r2l[love];
				if (teng(lft)) {
					r2l[love] = cur;
					l2r[cur] = love;
					return true;
				}
			}
		}
	}
	return false;
}

int main() {
	scanf("%d %d %d", &n, &m, &e);
	for(int i = 0; i < e; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		if(v > m)
			continue;
		edge[u][v] = true;
	}

	for(int i = 1; i <= n; ++i) {
		if(addMatch(i))
			++ans;
	}
	printf("%d\n", ans);
	return 0;
}
