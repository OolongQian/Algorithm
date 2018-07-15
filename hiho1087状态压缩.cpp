#include <iostream>
#include <vector> 
#include <cstring> 
using namespace std;
// #define _DEBUG
const int maxn = 15; 
const int maxstate = (1 << 12); 
bool grph[maxn][maxn]; 
int n, m; 
int maxs; 
int dp[maxstate][maxn]; 

void display(int x) {
    if(x == 0) cout << 0;
    while(x) {
        cout << (x & 1); 
        x = (x >> 1); 
    }
}

int main() {
    memset(grph, false, sizeof(grph)); 
    cin >> n >> m; 
    while(m--) {
        int u, v; 
        cin >> u >> v; 
        grph[u][v] = true; 
    }

    maxs = (1 << n); 
    for(int s = 0; s < maxs; ++s) {
        for(int i = 0; i <= n; ++i) {
            dp[s][i] = 0; 
        }
    }
    /**
    状态的压缩是符合一种递增的拓扑序列的，并且我们需要用到之前的停在各个节点的。
    */
    dp[1][1] = 1; 
    for(int s = 0; s < maxs; ++s) {
        if((s & 1) == 0) continue; 
        /// 这是指中途停留在i节点
        for(int i = 2; i <= n; ++i) {
#ifdef _DEBUG
            printf("calculate for dp["); 
            display(s); 
            printf("][%d]\n", i); 
#endif
            // 如果这个状态没有激活该节点。
            if( ((s >> (i - 1)) & 1) == 0) {
                dp[s][i] = 0; 
#ifdef _DEBUG
            printf("target node not activated... dp = 0\n"); 
#endif
            }
            else {
                // 如果这个状态删除了该节点之后就剩0了
                // 删除状态s中i节点的激活。
                int bitmask = ~(1 << (i - 1)); 
                int prevs = s & bitmask; 
                if(prevs == 0)  {
                    dp[s][i] = 1; 
#ifdef _DEBUG
                    printf("only one... dp = 1\n"); 
#endif
                }
                else if(prevs == 1) {
                    dp[s][i] = (int) grph[1][i];
                }
                else {
                    // 寻找剩下的1.
                    for(int j = 2; j <= n; ++j) {
                        if( ((prevs >> (j - 1)) & 1) == 1) {
#ifdef _DEBUG
                            printf("find child state dp["); 
                            display(prevs); 
                            printf("][%d]: %d\n", j, dp[prevs][j]); 
#endif
                            // 如果存在一条直接的路径能从j到i
                            if(grph[j][i]) {
                                dp[s][i] += dp[prevs][j];
#ifdef _DEBUG
                                printf("path exists\n"); 
                                printf("current val: %d\n", dp[s][i]); 
#endif
                            }
                            else {
#ifdef _DEBUG
                                printf("no path\n"); 
                                printf("current val: %d\n", dp[s][i]); 
    #endif
                            }
                        }
                    }
                }
            }
        }
    }
    int ans = 0; 
    for(int i = 2; i <= n; ++i) {
        if(grph[i][1])
            ans += dp[maxs - 1][i]; 
    }
    cout << ans << endl;
    return 0; 
}