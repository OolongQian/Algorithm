#include <iostream>
using namespace std;

struct node {
    int data; 
    node *next; 
};

void divide(node *&head, node *&mid, node *&tail) {

}

// quickSort needs divide and sort. 
void quickSort(node *&head, node *&tail) {
    node *mid; 
    divide(head, mid, tail); 
    quickSort(head, mid); 
    quickSort(mid->next, nullptr); 
}

// I want to do a quickSort, which needs to specify head and tail. 
// function wrapper. 
void quickSort(node *&head) {
    node *dummy = new node(); 
    dummy->next = head; 
    quickSort(dummy, nullptr); 
}


int main() {

    return 0; 
}