#include <iostream> 
#include <cstring> 
#include <vector> 
// #define _DEBUG
using namespace std;
const int maxn = 105; 
const int INVALID = -1e9; 
int n, k, m; 
int attr[maxn]; 
int ks[maxn]; 
bool must[maxn]; 
vector<int> grph[maxn]; 
int faz[maxn]; 
int dp[maxn][maxn]; 
int i2n[maxn]; 
int n2i[maxn]; 
int n2o[maxn]; 

void get_fa(int cur, int fa) {
    faz[cur] = fa; 
    for(int son : grph[cur]) {
        if(son == faz[cur]) continue; 
        get_fa(son, cur); 
    }
}

// check and mark. 
bool check() {
    static bool vis[maxn]; 
    memset(vis, false, sizeof(vis)); 
    int num = 0; 
    for(int i = 1; i <= k; ++i) {
        int cur = ks[i]; 
        while(cur != 0) {
            if(!vis[cur]) {
                ++num; 
                vis[cur] = true; 
                must[cur] = true; 
                cur = faz[cur]; 
            }
            else {
                break; 
            }
        }
    } 
#ifdef _DEBUG
    printf("nodes needed for must...");
    cout << num << endl;
#endif
    return num <= m; 
}

void get_dfs(int cur) {
    static int cnt = 0; 
    ++cnt; 
    n2i[cur] = cnt; 
    i2n[cnt] = cur; 
    for(int son : grph[cur]) {
        if(son == faz[cur]) continue; 
        get_dfs(son); 
    }
    n2o[cur] = cnt; 
}

int main() {
    memset(must, false, sizeof(must)); 
    cin >> n >> k >> m; 
    for(int i = 1; i <= n; ++i) cin >> attr[i]; 
    for(int i = 1; i <= k; ++i) {
        cin >> ks[i]; 
        must[ks[i]] = true; 
    }
    for(int i = 1; i <= n - 1; ++i) {
        int u, v; 
        cin >> u >> v; 
        grph[u].push_back(v); 
        grph[v].push_back(u); 
    }
    get_fa(1, 0); 
    if(!check()) {
        cout << -1 << endl;
    }
    else {
        // start a tree dp. 
        get_dfs(1); 
#ifdef _DEBUG
        cout << "node to dfs: "; 
        for(int i = 1; i <= n; ++i) {
            cout << n2i[i] << ' ';
        }
        cout << endl; 
        cout << "node to out: ";
        for(int i = 1; i <= n; ++i) {
            cout << n2o[i] << ' ';
        }
        cout << endl; 
        cout << "dfs to node: ";
        for(int i = 1; i <= n; ++i) {
            cout << i2n[i] << ' ';
        }
        cout << endl; 
#endif 
        // initialize dp. 
        for(int i = 1; i <= n; ++i) {
            for(int j = 0; j <= m; ++j) {
                dp[i][j] = -1e8; 
            }
        }
        for(int i = 1; i <= n; ++i) {
            if(!must[i2n[i]]) dp[i][0] = 0; 
            else dp[i][0] = INVALID; 
            dp[i][1] = attr[i2n[i]]; 
        }
        
        // start standard tree dp. 
        for(int i = n; i >= 1; --i) {
            /// 我们可以选取当前i，然后往后走一格。
            if(i != n) {
                for(int j = 1; j <= m; ++j) {
                    if(dp[i + 1][j - 1] == INVALID) dp[i][j] = INVALID; 
                    else dp[i][j] = dp[i + 1][j - 1] + attr[i2n[i]]; 
                }
            }
            /// 我们可以不选当前i，然后往后走一个子树。
            if(!must[i2n[i]]) {
                int u = n2o[i2n[i]] + 1;
                if(u <= n) {
                    /////////注意！！！不选的话j可以从1开始！
                    for(int j = 0; j <= m; ++j) {
                        if(dp[u][j] == INVALID) dp[i][j] = INVALID; 
                        else dp[i][j] = max(dp[i][j], dp[u][j]); 
                    }
                }
            }
#ifdef _DEBUG 
            printf("\n");
            for(int i = n; i >= 1; --i) {
                printf("display dfs %d...\n", i); 
                for(int j = 0; j <= m; ++j) {
                    printf("dp[%d][%d]: %d;  ", i, j, dp[i][j]); 
                }
                printf("\n"); 
            } 
#endif
        }
        cout << dp[1][m] << endl;
    }
    
    return 0; 
}