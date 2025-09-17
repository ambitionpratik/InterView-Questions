#include <bits/stdc++.h>
using namespace std;

void threadFunc(promise<int> myPromise) {
    myPromise.set_value(10);
}

void threadFunc1(promise<int>& myPromise) {
    myPromise.set_value(10);
}

int main() {
    promise<int> p;
    future<int> f{p.get_future()};
    
	thread t{threadFunc, move(p)};
	cout<<f.get()<<endl;
	t.join();
	
    promise<int> p1;
    future<int> f1{p1.get_future()};
    
	thread t1{threadFunc1, std::ref(p1)};
	//thread t1{threadFunc1, move(p1)}; // Error
	//thread t1{threadFunc1, p1}; // Error
	cout<<f1.get()<<endl;
	t1.join();
	
}

