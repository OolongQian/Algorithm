#include <iostream> 
using namespace std; 

const int maxn = 1e5 + 10; 
int l[maxn << 2], r[maxn << 2]; 
int dp[maxn << 2][10]; 
int b[maxn][4]; 
int n, q; 
int rt_init = 1; 
int ans[10]; 

void merge(int *cur, int *lft, int *rgt) {
    cur[1] = max(lft[1] + rgt[1], lft[2] + rgt[4]); 
    cur[1] = max(cur[1], lft[3] + rgt[7]); 

    cur[2] = max(lft[1] + rgt[2], lft[2] + rgt[5]); 
    cur[2] = max(cur[2], lft[3] + rgt[8]); 

    cur[3] = max(lft[1] + rgt[3], lft[2] + rgt[6]); 
    cur[3] = max(cur[3], lft[3] + rgt[9]); 

    cur[4] = max(lft[4] + rgt[1], lft[5] + rgt[4]); 
    cur[4] = max(cur[4], lft[6] + rgt[7]); 

    cur[5] = max(lft[4] + rgt[2], lft[5] + rgt[5]); 
    cur[5] = max(cur[5], lft[6] + rgt[8]); 

    cur[6] = max(lft[4] + rgt[3], lft[5] + rgt[6]); 
    cur[6] = max(cur[6], lft[6] + rgt[9]); 

    cur[7] = max(lft[7] + rgt[1], lft[8] + rgt[4]); 
    cur[7] = max(cur[7], lft[9] + rgt[7]); 

    cur[8] = max(lft[7] + rgt[2], lft[8] + rgt[5]); 
    cur[8] = max(cur[8], lft[9] + rgt[8]); 

    cur[9] = max(lft[7] + rgt[3], lft[8] + rgt[6]); 
    cur[9] = max(cur[9], lft[9] + rgt[9]); 
}

void build(int rt, int lft, int rgt) {
    l[rt] = lft; 
    r[rt] = rgt; 
    if(lft == rgt) {
        dp[rt][1] = b[lft][1];
        dp[rt][1] = max(dp[rt][1], b[lft][1] + b[lft][2]); 
        dp[rt][1] = max(dp[rt][1], b[lft][1] + b[lft][2] + b[lft][3]); 

        dp[rt][2] = b[lft][1] + b[lft][2];
        dp[rt][2] = max(dp[rt][2], b[lft][1] + b[lft][2] + b[lft][3]); 

        dp[rt][3] = b[lft][1] + b[lft][2] + b[lft][3]; 

        dp[rt][4] = b[lft][1] + b[lft][2];
        dp[rt][4] = max(dp[rt][4], b[lft][1] + b[lft][2] + b[lft][3]); 

        dp[rt][5] = b[lft][2]; 
        dp[rt][5] = max(dp[rt][5], b[lft][1] + b[lft][2]); 
        dp[rt][5] = max(dp[rt][5], b[lft][2] + b[lft][3]); 
        dp[rt][5] = max(dp[rt][5], b[lft][1] + b[lft][2] + b[lft][3]); 

        dp[rt][6] = b[lft][2] + b[lft][3]; 
        dp[rt][6] = max(dp[rt][6], b[lft][1] + b[lft][2] + b[lft][3]); 

        dp[rt][7] = b[lft][1] + b[lft][2] + b[lft][3]; 

        dp[rt][8] = b[lft][2] + b[lft][3]; 
        dp[rt][8] = max(dp[rt][8], b[lft][1] + b[lft][2] + b[lft][3]); 

        dp[rt][9] = b[lft][3]; 
        dp[rt][9] = max(dp[rt][9], b[lft][2] + b[lft][3]); 
        dp[rt][9] = max(dp[rt][9], b[lft][1] + b[lft][2] + b[lft][3]); 
        return; 
    }
    else {
        int mid = (lft + rgt) / 2;
        int lson = rt << 1; 
        int rson = rt << 1 | 1; 
        build(lson, lft, mid); 
        build(rson, mid + 1, rgt); 
        merge(dp[rt], dp[lson], dp[rson]); 
    }
} 

void query(int cur, int L, int R, int *ret) {
    if(l[cur] == L && r[cur] == R) {
        for(int i = 0; i < 10; ++i) {
            ret[i] = dp[cur][i]; 
        }
        return; 
    }
    else {
        int mid = (l[cur] + r[cur]) / 2; 
        if(R <= mid) {
            query(cur << 1, L, R, ret);
        }
        else if(mid < L) {
            query(cur << 1 | 1, L, R, ret); 
        }
        else {
            int ret1[10], ret2[10]; 
            query(cur << 1, L, mid, ret1);
            query(cur << 1 | 1, mid + 1, R, ret2); 
            merge(ret, ret1, ret2); 
        }
    }
}   

void display(int cur) {
#ifdef _DEBUG
    printf("node %d; [%d,%d]; \n", cur, l[cur], r[cur]); 
    for(int i = 1; i <= 9; ++i) {
        printf("%d: %d; ", i, dp[cur][i]); 
    }
    printf("\n"); 

    if(l[cur] != r[cur]) {
        display(cur << 1); 
        display(cur << 1 | 1); 
    }
#endif
}

int main() {
    cin >> n; 
    for(int i = 1; i <= 3; ++i) {
        for(int j = 1; j <= n; ++j) {
            cin >> b[j][i]; 
        }
    }

    build(rt_init, 1, n); 
    display(rt_init); 

    cin >> q; 
    while(q--) {
        int L, R; 
        int maxi = -1e9; 
        scanf(" %d %d", &L, &R); 
        query(rt_init, L, R, ans); 
        for(int i = 1; i <= 9; ++i) {
            maxi = max(maxi, ans[i]); 
        }
        printf("%d\n", maxi); 
    }
    return 0; 
}
