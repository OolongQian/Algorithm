#include <iostream>
#include <vector>
#include <memory>
#include <queue>
#include <cstdio>

// #define _DEBUG
using namespace std;

const int maxn = 1005;

struct pathT {
	int to, wgt;

	pathT(int a, int b) {
		to = a;
		wgt = b;
	}
};

struct edgeT {
	int u, v, wgt;

	edgeT(int a, int b, int c) {
		u = a;
		v = b;
		wgt = c;
	}
};


vector<pathT> grph[maxn];
//vector<pathT> rgrph[maxn];
vector<edgeT> redges;
int s, t, k;
int n, m;
int empirical_guess[maxn];  /// this is the shortest path from end node to current node.


struct qNodeT {
	int node;
	int dist;
	// int guess;
//	qNodeT(int a, int b, int c) {
	qNodeT(int a, int b) {
		node = a;
		dist = b;
//		guess = c;
	}
	bool operator< (const qNodeT& other) const {
//		return dist + guess < other.dist + other.guess;
		return dist + empirical_guess[node] < other.dist + empirical_guess[other.node];
	}
};
ostream& operator<<(ostream &os, const qNodeT &elem) {
//	os << elem.node << ' ' << elem.dist << ' ' << elem.guess;
	os << elem.node << ' ' << elem.dist << ' ' << empirical_guess[elem.node];
	return os;
}

/// dijkstra can't handle the case of replicated edges. use bellman-ford instead.
//void dijkstra(int beg) {
//	static bool vis[maxn];
//	static queue<int> q;
//
//	while(!q.empty()) q.pop();
//	memset(vis, false, sizeof(vis));
//	for(int i = 1; i <= n; ++i)
//		empirical_guess[i] = 0x3f3f3f3f;
//
//	q.push(beg);
//	empirical_guess[beg] = 0;
//
//	for(int i = 2; i <= n; ++i) {
//		int cur = -1, min_dist = 0x3f3f3f3f;
//		/// find which node to visit this time.
//		for(int j = 1; j <= n; ++j) {
//			if(!vis[j] && empirical_guess[j] < min_dist) {
//				min_dist = empirical_guess[j];
//				cur = j;
//			}
//		}
//		/// visit this node.
//		assert(cur != -1);
//		vis[cur] = true;
//		for(auto path : rgrph[cur]) {
//			int nxt = path.to;
//			int wgt = path.wgt;
//			if(!vis[nxt] && empirical_guess[cur] + wgt < empirical_guess[nxt]) {
//				empirical_guess[nxt] = empirical_guess[cur] + wgt;
//			}
//		}
//	}
//}
void BellmanFord(int cur) {
	for (int i = 1; i <= n; ++i)
		empirical_guess[i] = 0x3f3f3f3f;

	empirical_guess[cur] = 0;
	for (int i = 2; i <= n; ++i) {
		bool finish = true;

		// for (auto edge : redges) {
		for(int j = 0; j < redges.size(); ++j) {
			edgeT edge = redges[j];
			if (empirical_guess[edge.v] > empirical_guess[edge.u] + edge.wgt) {
				empirical_guess[edge.v] = empirical_guess[edge.u] + edge.wgt;
				finish = false;
			}
		}
		if (finish)
			break;
	}
}

int kShortestPath() {
	int times;
	if(s == t) times = -1;	/// if s and t equals, start point doesn't count for arrival.
	else times = 0;
	priority_queue<qNodeT> pq;

//	pq.push(qNodeT(s, 0, empirical_guess[s]));
		pq.push(qNodeT(s, 0));
//	pq.emplace(s, 0, empirical_guess[s]);
	while(!pq.empty()) {
		qNodeT tmp = pq.top();
		pq.pop();

		if(tmp.node == t) {
			++times;
			if(times == k)
				return tmp.dist;
		}

		for(int i = 0; i < grph[tmp.node].size(); i++) {
			pathT path = grph[tmp.node][i];
//		for(auto path : grph[tmp.node]) {
//			pq.push(qNodeT(path.to, tmp.dist + path.wgt, empirical_guess[path.to]));
			pq.push(qNodeT(path.to, tmp.dist + path.wgt));
//			pq.emplace(path.to, tmp.dist + path.wgt, empirical_guess[path.to]);
		}
	}
	return -1;
}
int main() {
#ifdef _DEBUG
	priority_queue<qNodeT> pq;
	pq.emplace(1, 1, 1);
	pq.emplace(1, 1, 2);
	pq.emplace(1, 2, 2);
	while(!pq.empty()) {
		cout << pq.top() << endl;
		pq.pop();
	}
#endif
	cin >> n >> m;

	while (m--) {
		int u, v, wgt;
		cin >> u >> v >> wgt;
		grph[u].push_back(pathT(v, wgt));
//		rgrph[v].push_back(pathT(u, wgt));
		redges.push_back(edgeT(v, u, wgt));
//		grph[u].emplace_back(v, wgt);
//		rgrph[v].emplace_back(u, wgt);
//		redges.emplace_back(v, u, wgt);
	}

	cin >> s >> t >> k;
	/**
	 * perform a search for shortest path in reversed order.
	 * */
//		dijkstra(t);
	BellmanFord(t);

	if(empirical_guess[s] == 0x3f3f3f3f) {
		printf("-1\n");
		return 0;
	}

#ifdef _DEBUG
	printf("shortest path after dijkstra: \n");
	for (int i = 1; i <= n; ++i) {
		printf("go from %d to %d: %d\n", t, i, empirical_guess[i]);
	}
#endif

	printf("%d\n", kShortestPath());
	return 0;
}
