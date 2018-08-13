#include <iostream>
using namespace std;

int lowerBound(int a[], int len, int x) {
    int low, high; 
    low = 0, high = len - 1; 
    
    while(low + 1 < high) {
        int mid = (low + high) / 2; 
        if(a[mid] > x) 
            high = mid - 1; 
        else 
            low = mid + 1; 
    }
    if(low == high) {
        if(a[low] > x)
            return low; 
        else 
            return low + 1; 
    }
    else {
        if(a[high] == x) 
            return high + 1; 
        else 
            return high; 
    }
}

int main() {
    int len; 
    int a[10]; 

    cout << "input length: ";
    cin >> len; 
    cout << "input a[]: ";
    for(int i = 0; i < len; ++i) 
        cin >> a[i];

    while(true) {
        int x; 
        cout << "find lower bound for: "; 
        cin >> x; 
        cout << lowerBound(a, len, x) << endl;
    }
    return 0; 
}