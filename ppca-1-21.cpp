#include <cstdio> 
#include <iostream> 
using namespace std;

const int maxn = 3005; 
int n, m; 
long long cost[maxn], val[maxn]; 
long long dp[maxn]; 

int main() {
    scanf("%d %d", &n, &m); 
    for(int i = 1; i <= m; ++i) {
        int w, v; 
        scanf("%d %d", &w, &v); 
        cost[i] = w; 
        val[i] = w * v; 
    }

    for(int i = 0; i <= n; ++i) {
        dp[i] = 0; 
    }

    for(int i = 1; i <= m; ++i) {
        for(int j = n; j >= 0; --j) {
            if(j - cost[i] >= 0) 
                dp[j] = max(dp[j], dp[j - cost[i]] + val[i]); 
            else 
                dp[j] = dp[j]; 
        }
    }
    printf("%lld\n", dp[n]); 
    return 0; 
}