#pragma once
#include <iostream>

class MyString {
private:
	char* str = nullptr;
	int size = 0; // excluding '\0'
	int capacity = 0;

	void copyFrom(const MyString& other);
	void resize(int newCapacity);
	void resize();
	int calculateCapacity(int size) const;
public:
	MyString() = default;
	explicit MyString(int size);
	MyString(const char* str);
	MyString(char ch);
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);
	~MyString();

	MyString(MyString&& other) noexcept;
	MyString& operator=(MyString&& other) noexcept;

	int getSize() const;
	char operator[](int pos) const;
	const char* getC_str() const;
	MyString getSubstring(int pos, int length) const;

	void pushBack(char ch);
	void append(const MyString& other);

	bool substringExists(const MyString& substr, int startPos = 0, int endPos = 0) const;

	friend MyString to_MyString(int num);
};

std::ostream& operator<<(std::ostream& os, const MyString& stream);
MyString operator+(const MyString& lhs, const MyString& rhs);
MyString to_MyString(int num);
