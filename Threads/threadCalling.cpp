#include <bits/stdc++.h>
using namespace std;

void ThreadFuncTakingValue(int i) {
    cout<<"ThreadFuncTakingValue::"<<i<<endl;
}

void ThreadFuncTakingRef(int &i) {
    cout<<"ThreadFuncTakingRef::Updating the value"<<endl;
    i += 5;
}

class MyFunctor {
    private:
        int m_val{};
        
    public:
        MyFunctor(const int& i) : m_val{i} {}
        
        void operator()() const {
            cout<<"MyFunctor::"<<m_val<<endl;
        }
};

class MyFunctorTakingRef {
    private:
        int& m_val;
    
    public:
        MyFunctorTakingRef(int& i) : m_val{i} {}
        
        void operator()() const {
            cout<<"MyFunctorTakingRef::Updating the value"<<endl;
            m_val += 5;
        }
};

class Request
{
    public:
        Request(const int& id) : m_id { id } { }
        void process() { cout << "Processing request " << m_id << endl; 
            m_result = m_id;
        }
        int getResult() { return m_result; }
        
    private:
        int m_id;
        int m_result{};
};

int main() {
	// Technique-1 (Function pointer)
	int val{10};
    thread t1{ThreadFuncTakingValue, val};
    thread t2{ThreadFuncTakingRef, std::ref(val)};
    
    t1.join();
    t2.join();
    
    // Technique-2 (Lambda)
    thread t3{[val] {
        cout<<"Lambda::"<<val<<endl;
    }};
    t3.join();
    
    thread t4{[&val] {
        cout<<"Lambda::Updating the value"<<endl;
        val += 5;
    }};
    t4.join();
    
    // Technique-3 (Functor)
    thread t5{MyFunctor{val}};
    t5.join();
    
    thread t6{MyFunctorTakingRef{val}};
    t6.join();
    
    // Technique-4 (Class method)
    Request req { val };
    thread t7{ &Request::process, &req };
    t7.join();
    //cout<<req.getResult()<<endl;
    
    //cout<<val<<endl;
}

