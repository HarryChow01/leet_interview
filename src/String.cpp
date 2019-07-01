
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

//http://blog.csdn.net/randyjiawenjie/article/details/6709539
//rhs = right hand side右手边，右操作数，lhs = left hand side左手边，左操作数

class String {
public:
    String(const char* str = nullptr);  //普通构造函数
    String(const String& rhs);  //拷贝构造函数
    String& operator=(const String &rhs);   //赋值函数
    ~String();

    String(String&& rhs) noexcept : data_(rhs.data_) {
        rhs.data_ = nullptr;
    }

    String& operator=(String&& rhs) {
        if (this != &rhs) {
            delete [] data_;
            data_ = rhs.data_;
            rhs.data_ = nullptr;
        }
        return *this;
    }
    /*
    String& operator=(String&& rhs) {
        swap(rhs);
        return *this;
    }*/
    void swap(String& rhs) {
        std::swap(data_, rhs.data_);
    }
    String operator+(const String& rhs);
    char& operator[](size_t index);
    friend std::ostream& operator<<(std::ostream& output, const String& rhs);

    char *get();
private:
    char *data_ = nullptr;
};

String::String(const char* str) {//不能像声明一样赋值NULL
    if (!str) {
        data_ = new char[1];
        *data_ = '\0';
    } else {
        size_t len = strlen(str);
        data_ = new char[len + 1];
        strcpy(data_, str);
    }
}

String::String(const String &rhs) {
    size_t len = strlen(rhs.data_);
    data_ = new char[len + 1];
    strcpy(data_, rhs.data_);
}

String& String::operator=(const String& rhs) {
    if(this == &rhs) {
        return *this;   //返回一个引用
    }
    delete [] data_;
    size_t len = strlen(rhs.data_);
    data_ = new char[len + 1];
    strcpy(data_, rhs.data_);
    return *this;
}

String::~String() {
    if (!data_) {
        delete [] data_;
        data_ = nullptr;
    }
}

//重载运算符+
String String::operator+(const String& rhs) {
    String newString;
    if ('\0' == *rhs.data_)
        newString = *this;
    else if ('\0' == *data_)
        newString = rhs;
    else {
        newString.data_ = new char[strlen(data_) + strlen(rhs.data_) + 1];
        strcpy(newString.data_, data_);
        strcat(newString.data_, rhs.data_);
    }
    return newString;
}
//重载下标运算符
char& String::operator[](const size_t index) {
    return data_[index];
}

//重载<<
std::ostream& operator<<(std::ostream& output, const String& rhs) {
    output << rhs.data_;
    return output;
}

char* String::get() {
    return this->data_;
}

int main() {
    String s1 = "abc";
    String s2 = "def";

    String s3 = s1 + s2;

    std::cout << "s3=" << s3 << std::endl;

    char ch = s1[1];
    std::cout << "ch=" << ch << std::endl;
}



