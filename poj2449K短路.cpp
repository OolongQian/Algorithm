#include <iostream> 
#include <vector> 
using namespace std;

const int maxn = 1005; 
struct pathT {
    int to, wgt; 
    pathT(int a, int b) {
        to = a; 
        wgt = b; 
    }
};
vector<pathT> grph[maxn]; 
vector<pathT> rgrph[maxn]; 
int s, t, k; 
int n, m; 

int main() {
    cin >> n >> m; 

    while(m--) {
        int u, v, wgt; 
        cin >> u >> v >> wgt; 
        graph[u].emplace
    }
    return 0; 
}