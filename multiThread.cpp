#include <iostream>
#include <thread> 
#include <mutex> 

using namespace std; 

mutex cout_mtx; 

/*
struct threadData {
    int tid; 
    int tval; 
} info;
*/

void threadFn(int id) {
    cout_mtx.lock();
    cout << "thread id is " << id << endl; 
    cout_mtx.unlock(); 
}

int main() {
    thread t1(threadFn, 1); 
    thread t2(threadFn, 2); 
    thread t3(threadFn, 3); 
    thread t4(threadFn, 4); 

    t1.join(); 
    t2.join();    
    t3.join(); 
    t4.join(); 

    return 0; 
}