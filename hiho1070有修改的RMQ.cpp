/**
 * 先mark着
*/
#include <iostream>
#include <cmath>
using namespace std;
// #define _DEBUG
const int maxn = 1e5 + 5;
int n, q;
int w[maxn];
int bsz;
struct blockT {
	int l, r;
	int v;
	blockT() {
		l = r = v = -1;
	}
} b[1500];

void pre_cal() {
	int cur_block = 0;
	int cur_sz = bsz;
	
	for(int i = 1; i <= n; ++i) {
		if(cur_sz == bsz) {
			b[cur_block].r = i - 1;
			cur_sz = 0;
			++cur_block;
			b[cur_block].l = i;
			b[cur_block].v = w[i];
			++cur_sz;
		}
		else {
			if(b[cur_block].v > w[i]) {
				b[cur_block].v = w[i];
			}
			++cur_sz;
		}
		if(i == n) {
			b[cur_block].r = n;
		}
	}
	
}

void display() {
#ifdef _DEBUG
	for(int i = 1; i < 1500; ++i) {
		if(b[i].l != -1) {
			printf("block %d, range [%d,%d]; min %d\n", i, b[i].l, b[i].r, b[i].v);
		}
	}
#endif
}

int query(int l, int r) {
    int cur_block = 1; 
    int ans = 1e9; 

    while(b[cur_block].r < l) ++cur_block; 
    while(b[cur_block].l <= r) {
        if(l <= b[cur_block].l && b[cur_block].r <= r) {
            ans = min(ans, b[cur_block].v); 
        }
        else if(l <= b[cur_block].l){
            for(int i = b[cur_block].l; i <= r; ++i) {
                ans = min(ans, w[i]); 
            }
        }
        else if(b[cur_block].r <= r) {
            for(int i = l; i <= b[cur_block].r; ++i) {
                ans = min(ans, w[i]); 
            }
        }
        else {
            for(int i = l; i <= r; ++i) {
                ans = min(ans, w[i]); 
            }
        }
        ++cur_block;
    }
    return ans; 
}

void modify(int id, int wgt) {
    w[id] = wgt; 
    int cur_block = 1; 
    while(id > b[cur_block].r) ++cur_block; 
    b[cur_block].v = 1e9; 
    for(int i = b[cur_block].l; i <= b[cur_block].r; ++i) {
        b[cur_block].v = min(b[cur_block].v, w[i]); 
    }
}

int main() {
	cin >> n;
	for(int i = 1; i <= n; ++i) {
		cin >> w[i];
	}
	bsz = (int) sqrt(n);
	
	pre_cal();
	display();
    
    cin >> q; 
    while(q--) {
        int op; 
        cin >> op; 
        if(op == 0) {
            int l, r; 
            scanf(" %d %d", &l, &r); 
            printf("%d\n", query(l, r)); 
        }
        else {
            int id, wgt; 
            scanf(" %d %d", &id, &wgt); 
            modify(id, wgt); 
            display();
        }
    }
	return 0;
}
