#include <iostream>
#include <cmath> 
using namespace std; 
// #define _DEBUG
const int maxn = 1e6 + 5; 
const int maxe = 21; 
int n, q; 
int w[maxn]; 
int st[maxn][maxe]; 

int _pow2(int e) {
    return (1 << e);
}

void pre_cal() {
    for(int e = 1; e < maxe; ++e) {
        int exp_range = _pow2(e); 
        int half_exp_range = _pow2(e - 1); 
        for(int s = 1; s + exp_range - 1 <= n; ++s) {
            st[s][e] = min(st[s][e - 1], st[s + half_exp_range][e - 1]); 
        }
    }
}

void display() {
#ifdef _DEBUG
    for(int s = 1; s <= n; ++s) {
        for(int e = 0; s + (int)pow(2, e) - 1 <= n; ++e) {
            printf("st[%d][%d]: %d\n", s, e, st[s][e]); 
        }
    }
#endif
}

int main() {
    scanf("%d", &n); 
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &st[i][0]); 
    }
    pre_cal();
    display(); 
    
    scanf("%d", &q); 
    while(q--) {
        int l, r, e, ans; 
        scanf(" %d %d", &l, &r); 
        if(l == r) e = 0; 
        else e = (int) floor(log2(r - l)); 
        ans = min(st[l][e], st[r + 1 - _pow2(e)][e]); 
        printf("%d\n", ans); 
    }
    return 0; 
}
