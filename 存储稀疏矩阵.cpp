#include <iostream>

using namespace std;

int findPrime(int k) {
    return k * 7 + 71; 
}

class sparseTable {
    private: 
        struct node {
            int row, col; 
            int val; 
            int state; // 0 means empty, 1 means deleted, 2 means active. 
            node(): state(0) {} 
        };
    private: 
        int dim;
        int size; 
        node *hashTable; 

        int hashFunc(int row, int col) const {
            return (row * dim + col) % size; 
        }
    public:
        // row and col are graph settings, and num is the expected number of elements. 
        sparseTable(int dim, int num):dim(dim) {
            size = findPrime(num); 
            hashTable = new node[size]; 
        }
        ~sparseTable() {
            delete [] hashTable; 
        }
        // insert a new edge into sparseTable. 
        void insert(int row, int col, int val) {
            int k, pos;
            pos = hashFunc(row, col); 
            k = 0; // current offset. 

            while(hashTable[pos].state == 2) {
                ++k; 
                pos = (pos + 2 * k - 1);
                if(pos >= size) 
                    pos -= size; 
            }
            // now hashTable[pos] ends up to be able to hold new val. 
            hashTable[pos].row = row; 
            hashTable[pos].col = col; 
            hashTable[pos].val = val; 
            hashTable[pos].state = 2; 
        }
        // find a particular edge, if it fails, return 0. 
        int find(int row, int col) {
            int k, pos;
            pos = hashFunc(row, col); 
            k = 0; // current offset. 

            while(hashTable[pos].state != 0) {
                if(hashTable[pos].state == 2 && hashTable[pos].row == row && hashTable[pos].col == col)
                    break; 
                else {
                    ++k;
                    pos += 2 * k - 1; 
                    if (pos >= size) 
                        pos -= size; 
                }
            }
            if(hashTable[pos].state == 2) 
                return hashTable[pos].val; 
            else 
                return 0; 
        }
        bool remove(int row, int col) {
            int k, pos;
            pos = hashFunc(row, col); 
            k = 0; // current offset. 

            while(hashTable[pos].state != 0) {
                if(hashTable[pos].state == 2 && hashTable[pos].row == row && hashTable[pos].col == col)
                    break; 
               else {
                    ++k;
                    pos += 2 * k - 1; 
                    if (pos >= size) 
                        pos -= size; 
                }
            }
            if(hashTable[pos].state == 2) {
                hashTable[pos].state = 1; 
                return true; 
            }
            else 
                return false; 
        }
};

int main() {
    sparseTable spt(1000, 50); 
    while(true) {
        char op; 
        int row, col; 
        cin >> op; 
        if (op == 'i') {
            int val; 
            cout << "insert. row, col, val: "; 
            cin >> row >> col >> val; 
            spt.insert(row, col, val); 
        }
        else if (op == 'r'){
            cout << "remove. row, col: "; 
            cin >> row >> col;
            spt.remove(row, col);
        }
        else {
            cout << "search. row, col: ";
            cin >> row >> col;
            cout << spt.find(row, col) << endl; 
        }
    }
    return 0; 
}