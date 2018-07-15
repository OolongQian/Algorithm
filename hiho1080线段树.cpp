#include <iostream>
#include <queue>
// #define _DEBUG
using namespace std;
/**
 * 规定顺序，先调整再加。
 */
const int maxn = 1e5 + 10;

int n, m;
int p[maxn];
int rt_init = 1;
int l_init, r_init;

struct nodeT {
	int l, r;
	int sum;
	int a_tag, g_tag;
	int sz;
	nodeT() {
		l = r = sum = sz = -1;
		a_tag = 0;
		g_tag = -1;
	}
} xds[maxn << 2];

void push_up(int cur) {
	xds[cur].sum = xds[cur << 1].sum + xds[cur << 1 | 1].sum;
	xds[cur].sz = xds[cur << 1].sz + xds[cur << 1 | 1].sz;
}

void push_down(int cur) {
	if(xds[cur].g_tag != -1) {
		int tag = xds[cur].g_tag;
		xds[cur].g_tag = -1;
        xds[cur << 1].a_tag = xds[cur << 1 | 1].a_tag = 0;
        xds[cur << 1].g_tag = xds[cur << 1 | 1].g_tag = tag;
        xds[cur << 1].sum = tag * xds[cur << 1].sz;
        xds[cur << 1 | 1].sum = tag * xds[cur << 1 | 1].sz;
	}
	if(xds[cur].a_tag != 0) {
		int tag = xds[cur].a_tag;
		xds[cur].a_tag = 0;
        xds[cur << 1].a_tag += tag;
        xds[cur << 1 | 1].a_tag += tag;
        xds[cur << 1].sum += tag * xds[cur << 1].sz;
        xds[cur << 1 | 1].sum += tag * xds[cur << 1 | 1].sz;
	}
}

void init_tre(int cur, int l, int r) {
	xds[cur].l = l;
	xds[cur].r = r;
	if(l == r) {
		xds[cur].sum = p[l];
		xds[cur].sz = 1;
		return;
	}
	else {
		int mid = (l + r) >> 1;
		init_tre(cur << 1, l, mid);
		init_tre(cur << 1 | 1, mid + 1, r);
		push_up(cur);
	}
}

void add(int cur, int l, int r, int v) {
	if(xds[cur].l == l && xds[cur].r == r) {
		xds[cur].a_tag += v; /// gugugu...
		xds[cur].sum += v * xds[cur].sz;
		return;
	}
	else {
		/// 要用到我的宝贝儿子们了。
		push_down(cur);
		int mid = (xds[cur].l + xds[cur].r) >> 1;
		if(r <= mid) {
			add(cur << 1, l, r, v);
		}
		else if(mid < l) {
			add(cur << 1 | 1, l, r, v);
		}
		else {
			add(cur << 1, l, mid, v);
			add(cur << 1 | 1, mid + 1, r, v);
		}
		push_up(cur);
	}
}

void change(int cur, int l, int r, int v) {
	if(xds[cur].l == l && xds[cur].r == r) {
		xds[cur].a_tag = 0;
		xds[cur].g_tag = v;
		xds[cur].sum = xds[cur].sz * v; /// gugugu...
		return;
	}
	else {
		/// 要用到我的宝贝儿子们了。
		push_down(cur);
		int mid = (xds[cur].l + xds[cur].r) >> 1;
		if(r <= mid) {
			change(cur << 1, l, r, v);
		}
		else if(mid < l) {
			change(cur << 1 | 1, l, r, v);
		}
		else {
			change(cur << 1, l, mid, v);
			change(cur << 1 | 1, mid + 1, r, v);
		}
		push_up(cur);
	}
}

void display() {
#ifdef _DEBUG
	queue<int> q;
	q.push(rt_init);
	while(!q.empty()) {
		int t = q.front();
		q.pop();
		printf("node %d; [%d,%d]; sum %d; size %d", t, xds[t].l, xds[t].r, xds[t].sum, xds[t].sz);
		if(xds[t].a_tag != 0) {
			printf(" add tag: %d", xds[t].a_tag);
		}
		if(xds[t].g_tag != -1) {
			printf(" g tag: %d", xds[t].g_tag);
		}
		printf("\n");
		
		if(xds[t].l != xds[t].r) {
			q.push(t << 1);
			q.push(t << 1 | 1);
		}
	}
#endif
}

int main() {
	cin >> n >> m;
	for(int i = 0; i <= n; ++i) {
		cin >> p[i];
	}
	l_init = 0;
	r_init = n;
	init_tre(rt_init, l_init, r_init);
	display();
	while(m--) {
		int op;
		scanf(" %d", &op);
		/// 加
		if(op == 0) {
			int l, r, v;
			scanf(" %d %d %d", &l, &r, &v);
			add(rt_init, l, r, v);
			display();
		}
		/// 调
		else {
			int l, r, v;
			scanf(" %d %d %d", &l, &r, &v);
			change(rt_init, l, r, v);
			display();
		}
        printf("%d\n", xds[rt_init].sum);
	}
	return 0;
}
