#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int a, c, k, m, n;

/// 倍增哈希.
const int maxn = 1e5 + 5;
const int maxm = 1e6 + 5;
const int maxexp = 20;
int zj_exp[maxm][30];				/// z jump exp
unsigned int str_exp[maxm][30];		/// string exp
unsigned int base = 103;
unsigned int baseExp[30];
/// z 可取 [0 - m)
char str[maxn];
int len;
unsigned int string_hashval;

bool check(int cur) {
	/// 得到从该位置开始长度为len的字符串。
	int e = maxexp;
	int length = len;
	int pos = cur;
	unsigned int hash_val = 0;

	while(length != 0) {
		while((1 << e) > length) --e;
		hash_val = hash_val * baseExp[e] + str_exp[pos][e];
		pos = zj_exp[pos][e];
		length -= (1 << e);
	}

	return hash_val == string_hashval;
}

int main() {
	cin >> a >> c >> k >> m >> n;
	baseExp[0] = base;
	for(int i = 1; i < maxexp; ++i) {
		baseExp[i] = baseExp[i - 1] * baseExp[i - 1];
	}
	// init.
	for(int i = 0; i < m; ++i) {
		zj_exp[i][0] = ((a * i + c) / k + m) % m;

		if(zj_exp[i][0] < m / 2) str_exp[i][0] = 0;
		else str_exp[i][0] = 1;
	}

	for(int e = 1; e <= maxexp; ++e) {
		for(int z = 0; z < m; ++z) {

			str_exp[z][e] = str_exp[z][e-1] * baseExp[e-1] + str_exp[zj_exp[z][e-1]][e-1];
			zj_exp[z][e] = zj_exp[zj_exp[z][e-1]][e-1];
		}
	}
#ifdef _DEBUG
	for (int e = 0; e < 5; ++e) {
		for (int i = 0; i < m; ++i) {
			printf("from %d with exp %d, hash_val: %lld\n", i, e, str_exp[i][e]);
		}
		cout << endl;
	}

	for (int e = 0; e < 5; ++e) {
		for (int i = 0; i < m; ++i) {
			printf("from %d with exp %d, transform to: %d\n", i, e, zj_exp[i][e]);
		}
		cout << endl;
	}
#endif
	scanf("%s", str);
	len = strlen(str);
	for(int i = 0; i < len; ++i) {
		string_hashval = string_hashval * base + str[i] - '0';
	}
	int ans = 0;
	for(int i = 0; i < m; ++i) {
		if(check(i))
			++ans;
	}
	cout << ans << endl;
	return 0;
}
