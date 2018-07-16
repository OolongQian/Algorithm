#include <iostream>
#include <cstring> 
#include <vector>
#include <queue> 
using namespace std;
#define _DEBUG
const int maxk = 20;
const int maxn = 1e5 + 5; 
const int maxm = 2e5 + 5;  
int n, m, k; 

struct edgeT {
    int to; 
    int l; 
    edgeT(int a, int b) {
        to = a; 
        l = b; 
    }
};

vector<edgeT> grph[maxn]; 
int dist[maxk][maxk]; 
int ks[maxk]; 
int d[maxn]; 

void dijkstra(int s) {
    static bool vis[maxn]; 
    memset(vis, false, sizeof(vis)); 
    for(int i = 1; i <= n; ++i) d[i] = 1e8; 
    d[s] = 0; 

    for(int i = 1; i <= n; ++i) {
        /// 找d最小的没有被访问过的。
        int v; 
        int dist = 1e8; 
        for(int nd = 1; nd <= n; ++nd) {
            if(d[nd] < dist && !vis[nd]) {
                dist = d[nd]; 
                v = nd;
            }
        }
        assert(dist != 1e8); 
        vis[v] = true; 
        for(auto e : grph[v]) {
            int nxt = e.to; 
            if(!vis[nxt] && d[nxt] > d[v] + e.l) {
                d[nxt] = d[v] + e.l; 
            }
        }
    }
#ifdef _DEBUG 
    for(int i = 1; i <= n; ++i) {
        printf("%d -> %d: %d\n", s, i, d[i]); 
    }
#endif
}

int main() {
    cin >> n >> m >>k; 

    for(int i = 1; i <= k; ++i) {
        cin >> ks[i]; 
    }

    for(int i = 1; i <= m; ++i) {
        int u, v, len; 
        cin >> u >> v >> len; 
        grph[u].push_back(edgeT(v, len)); 
        grph[v].push_back(edgeT(u, len));
    }

    ks[0] = 1; 
    ks[k + 1] = n; 
    for(int i = 0; i <= k + 1; ++i) {
        dijkstra(i); 
        for(int j = 0; j <= k + 1; ++j) {
            dist[i][j] = d[ks[j]]; 
        }
    }
    
#ifdef _DEBUG
    for(int i = 0; i <= k + 1; ++i) {
        for(int j = 0; j <= k + 1; ++j) {
            cout << dist[i][j] << ' ';
        }
        cout << endl;
    }
#endif
    
    return 0; 
}