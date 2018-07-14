#include <iostream>
#include <cstring>
using namespace std;
// #define _DEBUG 

const int maxn = 1e6 + 5;
const int maxm = 1e4 + 5; 
char p[maxm];
char str[maxn]; 
int lp; 
int ls; 
int nxt[maxm]; 

void KMP() {
    int num = 0; 

    cin >> p >> str; 
    lp = strlen(p); 
    ls = strlen(str);     

    for(int i = 0; i < lp; ++i) {
        nxt[i] = -1; 
    }
    
    int k = -1; 
    for(int i = 1; i < lp; ++i) {
        k = nxt[i - 1]; 
        while(k != -1 && p[k + 1] != p[i]) {
            k = nxt[k]; 
        }
        if(p[k + 1] == p[i]) {
            nxt[i] = k + 1; 
        }
        else {
            nxt[i] = -1; 
        }
    }
#ifdef _DEBUG
    for(int i = 0; i < lp; ++i) {
        cout << nxt[i] << ' ';
    }
    cout << endl;
#endif

    /// use nxt pattern to match 
    k = -1;  
    for(int i = 0; i < ls; ++i) {
        while(k != -1 && p[k + 1] != str[i]) {
            k = nxt[k]; 
        }
        if(p[k + 1] == str[i]) {
            ++k;
            if(k == lp - 1) {
                ++num;
                k = nxt[k];
            }
        }
    }
    cout << num << endl;
}   


int main() {
    int n; 
    cin >> n; 
    while(n--) {
        KMP();
    }
    return 0; 
}