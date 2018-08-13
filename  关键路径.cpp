#include <iostream>
#include <queue> 
using namespace std;

const int Vers = 10; 

void findCriticalPath() {
    int *ee = new int[Vers]; // 最早发生时间。
    int *le = new int[Vers]; // 最晚发生时间。
    int *topo = new int[Vers]; // 拓扑排序。
    int topo_len = 0; 
    int *inDegree = new int[Vers]; 
    queue<int> q; 
    // 先找到拓扑序列。
    // 计算入度。
    for (int i = 0; i < Vers; ++i) {
        for(edgeNode *p = verList[i].head; p != nullptr; p = p->next) {
            ++inDegree[p->end];
        }
    }

    for(int i = 0; i < Vers; ++i) 
        if(inDegree[i] == 0) q.push(i); 
    
    while(!q.empty()) {
        int cur = q.front(); q.pop(); 
        topo[topo_len++] = cur; 
        for(edgeNode *p = verList[cur]; p != nullptr; p = p->next) {
            --inDegree[p->end]; 
            if(inDegree[p->end] == 0)
                q.push(p->end); 
        }
    }
    // 现在我已经得到了拓扑序列，开始找关键路径了。
    // 找最早发生时间，顺序遍历拓扑序列，每次更新它所链接的顶点，因为是有向图，不用管父亲问题。
    // 初始化。
    for(int i = 0; i < Vers; ++i) ee[i] = 0; 
    for(int i = 0; i < Vers; ++i) {
        int cur = topo[i]; 
        for(edgeNode *p = verList[cur]; p != nullptr; p = p->next) {
            ee[p->end] = max(ee[p->end], ee[cur] + p->weight); 
        }
    }

    // 找最晚发生时间，逆序遍历拓扑序列，每次更新它所逆向连接的顶点，因为是有向图，不用管父亲问题。
    // 初始化。
    for(int i = 0 ; i < Vers; ++i) le[i] = ee[topo[Vers - 1]]; 
    for(int i = Vers - 1; i >= 0; --i) {
        int cur = topo[i]; 
        for(edgeNode *p = verList[cur]; p != nullptr; p = p->next) {
            le[cur] = min(le[cur], le[p->end] - p->weight); 
        }
    }

    // 按照拓扑序列打印关键路径。
    for(int i = 0; i < Vers; ++i) {
        if(ee[i] == le[i])
            cout << verList[topo[i]].ver << ' ' << ee[i] << endl;
    }
}