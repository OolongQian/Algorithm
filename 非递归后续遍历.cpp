// 我觉得非递归后续遍历只需要进栈两次，但是书上进栈了三次，而且我觉得所有非递归问题都只需要进栈两次。
// 我创建一棵树，然后进行递归和非递归的后续遍历。

#include <iostream>
#include <stack> 
using namespace std;

const char mark = '@'; 

struct node {
    char val; 
    node *lch; 
    node *rch; 
};
void tree_init(node *rt) {
    printf("输入根结点"); 
    cin >> rt->val;

    stack<node*> s;
    s.push(rt); 
    while(!s.empty()) {
        node *cur = s.top(); s.pop();
        node *lch = new node(); 
        node *rch = new node(); 

        printf("输入节点%c的两个儿子（%c代表空节点）：", cur->val, mark); 
        cin >> lch->val >> rch->val; 
        if (rch->val != mark) {
            rch->lch = rch->rch = nullptr; 
            cur->rch = rch; 
            s.push(rch); 
        }
        if (lch->val != mark) {
            lch->lch = lch->rch = nullptr; 
            cur->lch = lch; 
            s.push(lch); 
        }

    }
}

void post_order(node *root) {
    if(root->lch != nullptr)
        post_order(root->lch); 
    if(root->rch != nullptr)
        post_order(root->rch); 
    cout << root->val << ' '; 
}

struct wrap {
    node *nd; 
    int time; 
    wrap(node *p, int i): nd(p), time(i) {}
};

void un_recursive_post_order(node *root) {
    stack<wrap> s;
    s.push(wrap(root, 1)); 

    while(!s.empty()) {
        wrap cur = s.top(); s.pop(); 

        if(cur.time == 1) {
            cur.time = 2;
            s.push(cur); 
            if(cur.nd->rch != nullptr) 
                s.emplace(cur.nd->rch, 1); 
            if(cur.nd->lch != nullptr) 
                s.emplace(cur.nd->lch, 1);
        }
        else if(cur.time == 2) {
            cout << cur.nd->val << ' '; 
        }
    }
}

int main() {
    node *root = new node(); 
    tree_init(root); 
    post_order(root); 
    cout << endl;
    un_recursive_post_order(root); 
    cout << endl;
    return 0; 
}