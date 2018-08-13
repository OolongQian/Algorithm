#include <iostream> 
using namespace std;

double median(int s1[], int s2[], int len) {
    // 中位数为平均数。
    if(len == 1) {
        return (s1[0] + s2[0]) / 2.0; 
    }
    // 找小数里面的大数，和大数里面的小数。
    else if(len == 2) {
        return (max(s1[0], s2[0]) + min(s1[1], s2[1])) / 2.0; 
    }
    else {
        int mid_pos = (len + 1) / 2 - 1; 
        int s1_median = s1[mid_pos]; 
        int s2_median = s2[mid_pos]; 
        if(s1_median > s2_median) 
            // 我们删去比s1_median大的元素，以及比s2_median小的元素。
            return median(s1, s2 + mid_pos, len - mid_pos); 
        else 
            return median(s1 + mid_pos, s2, len - mid_pos); 
    }
}

int main() {
    int len; 
    int s1[100]; 
    int s2[100]; 
    while(true) {
        cout << "请输入数组长度：";
        cin >> len; 

        cout << "请输入s1：";
        for(int i = 0; i < len; ++i) 
            cin >> s1[i]; 

        cout << "请输入s2：";
        for(int i = 0; i < len; ++i) 
            cin >> s2[i]; 

        cout << "中位数为：" << median(s1, s2, len) << endl; 
            
    }
    return 0; 
}
