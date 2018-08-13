#include <iostream>
#include "limits.h"
using namespace std;

const int INIT_NODE = 0; 
const int Vers = 10; 
void prim() {
    bool vis[Vers]; 
    int startNode[Vers]; 
    int lowCost[Vers]; 

    // 初始化lowCost为最大值，初始化vis为全部false。
    for(int i = 0; i < Vers; ++i) {
        vis[i] = false; 
        lowCost[i] = INT_MAX; 
    }
    // 我们从一个指定的init节点开始，或者默认从0号节点开始prim算法。
    lowCost[INIT_NODE] = 0; 

    // 每次选择一个节点进入生成树，当选择了Vers个节点后，生成树就生成啦！
    for(int i = 0; i < Vers; ++i) {
        // 每次选择没有被拿来更新过的，并且距离已经选择的生成树最短的节点。
        int min_cost = INT_MAX, start; 
        for(int j = 0; j < Vers; ++j) {
            if(!vis[j] && lowCost[j] < min_cost) {
                start = j; 
                min_cost = lowCost[j]; 
            }
        }
        // 把当前节点标记为已经使用过。
        vis[start] = true; 
        for(edgeNode *p = verList[start]; p != nullptr; p = p->next) {
            if(lowCost[start] + p->weight < lowCost[p->end]) {
                lowCost[p->end] = lowCost[start] + p->weight; 
                startNode[p->end] = start; 
            }
        }
    }
    // 输出最小生成树，虽然第一个顶点输出的时候，它没有startNode，所以很吃屎。
    for(int i = 0; i < Vers; ++i) {
        cout << startNode[i] << "->" << i << ": " << lowCost[i] << endl;
    }
}