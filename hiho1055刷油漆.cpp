#include <iostream> 
#include <vector> 
using namespace std;

const int maxn = 105; 
int n, m; 
int sc[maxn]; 
vector<int> tre[maxn]; 
int dp[maxn][maxn];
int i2n[maxn];  // in to node
int n2i[maxn];
int n2o[maxn];  // node to out

void dfs(int cur, int fa) {
    static int cnt = 0; 
    ++cnt; 
    n2i[cur] = cnt; 
    i2n[cnt] = cur; 

    for(int son : tre[cur]) {
        if(son == fa) continue; 
        dfs(son, cur); 
    }
    n2o[cur] = cnt; 
}

int main() {
    cin >> n >> m; 
    
    for(int i = 1; i <= n; ++i) {
        cin >> sc[i]; 
    }

    for(int i = 1; i <= n - 1; ++i) {
        int u, v;
        cin >> u >> v; 
        tre[u].push_back(v); 
        tre[v].push_back(u); 
    }

    dfs(1, 0); 

#ifdef _DEBUG
    cout << "i2n: "; 
    for(int i = 1; i <= n; ++i) {
        cout << i2n[i] << ' ';
    } 
    cout << endl;

    cout << "n2i: "; 
    for(int i = 1; i <= n; ++i) {
        cout << n2i[i] << ' ';
    } 
    cout << endl;

    cout << "n2o: "; 
    for(int i = 1; i <= n; ++i) {
        cout << n2o[i] << ' ';
    } 
    cout << endl;
#endif

    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j <= m; ++j) {
            dp[i][j] = -1e8; 
        }
    }
    for(int i = 1; i <= n; ++i) {
        dp[i][0] = 0; 
    }

    /// 进行dp
    for(int i = n; i >= 1; --i) {
        dp[i][1] = sc[i2n[i]]; 
        /// 我们可以选取当前i，然后往后走一格。
        if(i != n) {
            for(int j = 2; j <= m; ++j) {
                dp[i][j] = dp[i + 1][j - 1] + sc[i2n[i]]; 
            }
        }
        /// 我们可以不选当前i，然后往后走一个子树。
        int u = n2o[i2n[i]] + 1;
        if(u <= n) {
            /////////注意！！！不选的话j可以从1开始！
            for(int j = 1; j <= m; ++j) {
                dp[i][j] = max(dp[i][j], dp[u][j]); 
            }
        }
    }
    cout << dp[1][m] << endl;
    return 0; 
}