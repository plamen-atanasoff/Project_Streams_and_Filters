#pragma once

template <typename T>
class DynamicArray {
private:
	T** values = nullptr;
	int size = 0;
	int capacity = 0;

	void resize();
public:
	DynamicArray() = default;
	DynamicArray(const DynamicArray<T>& other) = delete;
	DynamicArray<T>& operator=(const DynamicArray<T>& other) = delete;
	~DynamicArray();

	void add(const T& element);

	int getSize() const;
	const T& operator[](int pos) const;
	T& operator[](int pos);
};

template <typename T>
void DynamicArray<T>::resize() {
	assert(size <= capacity);
	int newCapacity = capacity == 0 ? 4 : capacity * 2;
	T** tempValues = new T * [newCapacity];
	for (int i = 0; i < size; ++i) {
		tempValues[i] = values[i];
	}

	values = tempValues;
	capacity = newCapacity;
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
	for (int i = 0; i < size; ++i) {
		delete values[i];
	}
	delete[] values;
}

template <typename T>
void DynamicArray<T>::add(const T& element) {
	if (size == capacity) {
		resize();
	}
	values[size] = element.clone();
	size++;
}

template <typename T>
int DynamicArray<T>::getSize() const {
	return size;
}

template <typename T>
const T& DynamicArray<T>::operator[](int pos) const {
	assert(pos >= 0 && pos < size);
	return *values[pos];
}

template <typename T>
T& DynamicArray<T>::operator[](int pos) {
	assert(pos >= 0 && pos < size);
	return *values[pos];
}
