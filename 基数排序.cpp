#include <iostream>
using namespace std;

// 基数排序，进bucket和出bucket的顺序并没有严格规定，也就是说进bucket时，可以挂下去，也可以插进去。
// 但是要注意的是：bucket必须满足队列的性质，先进去必须要先出来，否则前一位上基数排序的成果就不能被应用到
// 下一轮排序当中。

struct node { 
    int data; 
    node *next; 
};

void bucketSort(node *&p) { 
    // 定义需要使用的变量，其中bucket为10个桶，last记录着每个桶链表的最后一个元素，方便取链表，
    // 而tail记录了待排序链表p的最后一个元素。
    node *bucket[10], *last[10], *tail; 

    // 找到最大元素，计算需要桶排序的位数。
    int max_elem = INT_MIN; 
    int len; 
    for(tail = p; tail != nullptr; tail = tail->next) {
        max_elem = max(max_elem, tail->data); 
    }
    
    len = 0; 
    while(max_elem != 0) {
        max_elem /= 10; 
        ++len; 
    }
    
    // 桶排序千万不要一个激动忘记了要多次排序哇！！！
    for(int i = 0; i < len; ++i) {
        // 把这些元素都放到各自的桶里面。
        for(tail = p; tail != nullptr; tail = tail->next) {
            // 预处理这些元素。
            int pos = tail->data; 
            for(int j = 0; j < i; ++j) {
                pos /= 10; 
            }
            pos %= 10; 

                    // 如果桶现在还是空的。
            if(bucket[pos] == nullptr) {
                bucket[pos] = tail; 
                last[pos] = tail; 
            }
            else {
                last[pos]->next = tail; 
                last[pos] = last[pos]->next; 
            }
        }
        // 把桶里面的元素全部都拿出来。
        p = tail = nullptr; 
        for(int i = 0; i < 10; ++i) {
            // 如果桶是空的，我们就不管它啦。
            if(bucket[i] == nullptr) continue; 
            // 如果桶非空，我们开始拿数据。
            else {
                // 如果头是空的，我的天呐。
                if(p == nullptr) {
                    p = bucket[i];  
                    tail = last[i]; 
                }
                // 如果头非空，我们需要把尾巴连起来哦。
                else {
                    tail->next = bucket[i]; 
                    tail = last[i]; 
                }
            }
        }
        // 一次排序结束，我们需要清空bucket，因为链表的桶排序的空间复杂度为O(1)，我们不用担心数据丢失的问题。
        for(int i = 0; i < 10; ++i) 
            bucket[i] = last[i] = nullptr; 
        tail = nullptr; 
    }
}
