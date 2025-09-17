
#include <bits/stdc++.h>
using namespace std;

mutex m{};
condition_variable cv{};
int cnt{1};

void printOdd() {
    while(cnt < 50) {
        unique_lock<mutex> lock(m);
        
        cv.wait(lock, []{ return cnt % 2 != 0; });
        
        cout << cnt << endl;
        
        cnt++;
        
        lock.unlock();
        
        cv.notify_all();
    }
}

void printEven() {
    while(cnt <= 50) {
        unique_lock<mutex> lock(m);
        
        cv.wait(lock, []{ return cnt % 2 == 0; });
        
        cout << cnt << endl;
        
        cnt++;
        
        lock.unlock();
        
        cv.notify_all();
    }
}

int main() {

    thread t1{printOdd};
    
    thread t2{printEven};
    
    t1.join();
    t2.join();
}

