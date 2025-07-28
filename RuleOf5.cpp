#include <iostream>
#include <cstring>

class MyString {
private:
    char* data;

public:
    // Constructor
    MyString(const char* str = "") {
        std::cout << "Constructor\n";
        data = new char[strlen(str) + 1];
        std::strcpy(data, str);
    }

    // Destructor
    ~MyString() {
        std::cout << "Destructor\n";
        delete[] data;
    }

    // Copy Constructor
    MyString(const MyString& other) {
        std::cout << "Copy Constructor\n";
        data = new char[strlen(other.data) + 1];
        std::strcpy(data, other.data);
    }

    // Copy Assignment Operator
    MyString& operator=(const MyString& other) {
        std::cout << "Copy Assignment\n";
        if (this == &other)
            return *this;
        delete[] data;
        data = new char[strlen(other.data) + 1];
        std::strcpy(data, other.data);
        return *this;
    }

    // Move Constructor
    MyString(MyString&& other) noexcept {
        std::cout << "Move Constructor\n";
        data = other.data;
        other.data = nullptr;
    }

    // Move Assignment Operator
    MyString& operator=(MyString&& other) noexcept {
        std::cout << "Move Assignment\n";
        if (this == &other)
            return *this;
        delete[] data;
        data = other.data;
        other.data = nullptr;
        return *this;
    }

    // For display
    void print() const {
        std::cout << (data ? data : "null") << '\n';
    }
};
