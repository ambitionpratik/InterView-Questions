#include <bits/stdc++.h>
using namespace std;

template<typename T>
class MyVector {

public:

    // Default c'tor
    MyVector() {
    }

    // Initializer list c'tor
    MyVector(initializer_list<T> list) {
        const size_t lSize{ list.size() };
        m_size = lSize;
        m_capacity = m_size + 1;

        m_ptr = new T[m_capacity];

        auto i{ 0 };
        for (const auto& e : list) {
            m_ptr[i++] = e;
        }
    }

    // Size based c'tor
    MyVector(size_t size) {
        m_size = size;
        m_capacity = m_size + 1;

        m_ptr = new T[m_capacity];

        for (auto i{ 0 }; i < size; ++i) {
            m_ptr[i] = 0;
        }
    }

    T& operator[](size_t index) {
        return m_ptr[index];
    }

    void Push_Back(const T& data) {
        if (m_size > 0 && m_size >= m_capacity) {
            m_capacity *= static_cast<size_t>(2);
            _reallocate();

            m_ptr[m_size] = data;
            m_size++;
        }
        else {
            if (m_size == 0) {
                m_ptr = new T[m_capacity];
            }
            m_ptr[m_size] = data;
            m_size++;
        }
    }

    size_t Size() { return m_size; }
    size_t Capacity() { return m_capacity; }

private:
    T* m_ptr{ nullptr };
    size_t m_size{};
    size_t m_capacity{ 1 };

    void _reallocate() {

        // Temporary array 
        T* tPtr = new T[m_capacity];

        // Copy data from existing pointer
        for (auto i{ 0 }; i < m_size; ++i) {
            tPtr[i] = m_ptr[i];
        }
        delete[] m_ptr;

        m_ptr = tPtr;
    }
};

int main() {
    // your code goes here
    //MyVector<int> emptyVector;
    // emptyVector.Push_Back(10);
    // emptyVector.Push_Back(20);
    // emptyVector.Push_Back(30);
    // emptyVector.Push_Back(40);
    // emptyVector.Push_Back(50);

    // cout<<emptyVector.Size() << ", " << emptyVector.Capacity() << endl;
    // cout<<emptyVector[2]<<endl;

    MyVector<int> initializerVector{ 1,2,3 };

    initializerVector.Push_Back(4);
    initializerVector.Push_Back(5);
    initializerVector.Push_Back(6);
    initializerVector.Push_Back(7);
    initializerVector.Push_Back(8);
    initializerVector.Push_Back(9);

    cout << initializerVector.Size() << ", " << initializerVector.Capacity() << endl;

    cout << initializerVector[5] << endl;

    //MyVector<int> sizeVector(5);


    //cout<<emptyVector.Size() << ", " << emptyVector.Capacity() << endl;
    //cout<<sizeVector.Size() << ", " << sizeVector.Capacity() << endl;

    //cout<<initializerVector[2]<<endl;
    //cout<<sizeVector[1]<<endl;
}
