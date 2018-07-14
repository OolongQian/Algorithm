#include <iostream>
using namespace std; 
const int maxn = 1005; 
const int maxstate = 1024; 

int wst[maxn]; 
int n, m, q; 
int dp[maxn][maxstate]; 

/**
 * 注意：状态压缩dp当中有大量富余的无效状态，我要学会习惯不处理它们，放任它们处于一种无效的状态之中，
 * 在最终的筛除阶段不受影响即可。
*/

int get_bits_sum(int x) {
    int ans = 0; 
    while(x) {
        if(x & 1) ++ans; 
        x = (x >> 1); 
    }
    return ans; 
}

int main() {
    cin >> n >> m >> q; 
    for(int i = 1; i <= n; ++i) {
        cin >> wst[i]; 
    }

    /**
     * 每当遇到动态规划当中不可触及的状态时，不要惊慌，用一个很小或者很大的值来抵消max或者min的影响，
     * 或者用一个题目中不出现的tag来标识它，手动处理。
    */
    for(int i = 0; i < maxn; ++i) {
        for(int j = 0; j < maxstate; ++j) {
            dp[i][j] = -1; 
        }
    }   
    
    /// 每个状态记录包括自己在内的m个bit。
    dp[0][0] = 0; 
    for(int i = 1; i <= n; ++i) {
        /**
         * 动态规划思想：通过子问题的状态来更新大问题的状态。
         * 当子问题被遍历过之后，大问题会达到最优解。 
        */
        for(int _prev = 0; _prev < maxstate; ++_prev) {
            /* 手动筛除。
            if(dp[i - 1][_prev] == -1) 
                continue; 
            */
            // 如果还有空余，我可以清除i地的垃圾。
            if(get_bits_sum(_prev / 2) < q) {
                int choose_state = (_prev >> 1) | 1 << (m - 1);
                dp[i][choose_state] = max(dp[i][choose_state], dp[i - 1][_prev] + wst[i]);  
            }
            // 不论有没有空余，我都是可以放任i地的垃圾的。
            int no_choose_state = (_prev >> 1); 
            dp[i][no_choose_state] = max(dp[i][no_choose_state], dp[i - 1][_prev]); 
        }
    }
    
    /// 扫一遍，筛除最大的。
    int max_wst = -1;
    for(int i = 0; i < maxstate; ++i) {
        if(max_wst < dp[n][i]) {
            max_wst = dp[n][i]; 
        }
    }
    cout << max_wst << endl;
    return 0; 
}
