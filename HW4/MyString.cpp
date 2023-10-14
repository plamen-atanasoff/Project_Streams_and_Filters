#define _CRT_SECURE_NO_WARNINGS
#include "MyString.h"
#include <cstring>
#include <cassert>
#include <algorithm>
#include <cstdlib>
#include <sstream>
#include <utility>

int MyString::calculateCapacity(int size) const {
    int neededCapacity = 1;
    while (size >= neededCapacity) {
        neededCapacity *= 2;
    }
    return neededCapacity;
}

void MyString::copyFrom(const MyString& other) {
    if (other.str) {
        char* newStr = new char[other.capacity];
        strcpy(newStr, other.str);
        delete[] str;
        str = newStr;
    }
    else {
        delete[] str;
        str = nullptr;
    }

    size = other.size;
    capacity = other.capacity;
}

void MyString::resize(int newCapacity) {
    assert(newCapacity > 0);
    char* newStr = new char[newCapacity];
    if (str) {
        strcpy(newStr, str);
    }
    delete[] str;
    str = newStr;
    capacity = newCapacity;
}

void MyString::resize() {
    int newCapacity = capacity == 0 ? 2 : capacity * 2;
    resize(newCapacity);
}

MyString::MyString(int size) : capacity(calculateCapacity(size)) {
    str = new char[capacity];
    str[0] = '\0';
}

MyString::MyString(const char* str) {
    size = strlen(str);
    capacity = calculateCapacity(size);
    this->str = new char[capacity];
    strcpy(this->str, str);
}

MyString::MyString(char ch) {
    pushBack(ch);
}

MyString::MyString(const MyString& other) {
    copyFrom(other);
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        copyFrom(other);
    }
    return *this;
}

MyString::~MyString() {
    delete[] str;
}

MyString::MyString(MyString&& other) noexcept {
    std::swap(other.str, str);
    std::swap(other.size, size);
    std::swap(other.capacity, capacity);
}

MyString& MyString::operator=(MyString&& other) noexcept {
    if (this != &other) {
        std::swap(other.str, str);
        std::swap(other.size, size);
        std::swap(other.capacity, capacity);
    }
    return *this;
}

int MyString::getSize() const {
    return size;
}

char MyString::operator[](int pos) const {
    assert(pos >= 0 && pos < size);
    return str[pos];
}

const char* MyString::getC_str() const {
    assert(size > 0);
    return str;
}

MyString MyString::getSubstring(int pos = 0, int length = 0) const {
    assert(pos >= 0 && pos < size);
    MyString substr(length + 1);
    substr.size = length;
    memcpy(substr.str, str + pos, length);
    substr.str[length] = '\0';
    return substr;
}

void MyString::pushBack(char ch) {
    if (size + 1 >= capacity) {
        resize();
    }
    str[size++] = ch;
    str[size] = '\0';
}

void MyString::append(const MyString& other) {
    int newSize = size + other.size;
    if (newSize >= capacity) {
        resize(calculateCapacity(newSize));
    }
    memcpy(str + size, other.str, other.size);
    str[newSize] = '\0';
    size = newSize;
}

bool MyString::substringExists(const MyString& substr, int startPos, int endPos) const { //endPos is exclusive
    assert(startPos >= 0 && startPos < size);
    assert(endPos >= 0 && endPos <= size);
    assert(startPos < endPos);
    const char* begPtr = str + startPos;
    const char* encounterPtr = strstr(begPtr, substr.str);
    if (!encounterPtr) {
        return false;
    }
    else if ((encounterPtr - begPtr) + substr.getSize() <= static_cast<size_t>(endPos) - startPos) {
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const MyString& stream) {
    os << stream.getC_str();
    return os;
}

MyString operator+(const MyString& lhs, const MyString& rhs) {
    MyString res(lhs);
    res.append(rhs);
    return res;
}

MyString to_MyString(int num) {
    MyString res;
    std::stringstream s;
    s << num;

    char ch;
    while (s >> ch) {
        res.pushBack(ch);
    }
    return res;
}
