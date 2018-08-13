#include <iostream>
#include <stack>
using namespace std;

void in_order(int a[], int len, int idx) {
    if(idx * 2 <= len) 
        in_order(a, len, idx * 2); 

    cout << a[idx] << ' '; 

    if(idx * 2 + 1 <= len)
        in_order(a, len, idx * 2 + 1); 
}

void in_order(int a[], int len) {
    in_order(a, len, 1); 
    cout << endl;
}

int main() {
    int a[] = {0, 1, 9, 4, 3, 6, 4, 8, 10}; 
    in_order(a, 8); 
    return 0; 
}