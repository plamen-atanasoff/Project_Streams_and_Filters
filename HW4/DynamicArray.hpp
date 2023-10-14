#pragma once

template <typename T>
class DynamicVector {
private:
	T** values = nullptr;
	int size = 0;
	int capacity = 0;

	void resize();
public:
	DynamicVector() = default;
	DynamicVector(const DynamicVector<T>& other) = delete;
	DynamicVector<T>& operator=(const DynamicVector<T>& other) = delete;
	~DynamicVector();

	void add(const T& element);

	int getSize() const;
	const T& operator[](int pos) const;
	T& operator[](int pos);
};

template <typename T>
void DynamicVector<T>::resize() {
	assert(size <= capacity);
	int newCapacity = capacity == 0 ? 4 : capacity * 2;
	T** tempValues = DBG_NEW T * [newCapacity];
	for (int i = 0; i < size; ++i) {
		tempValues[i] = values[i];
	}

	values = tempValues;
	capacity = newCapacity;
}

template <typename T>
T& DynamicVector<T>::operator[](int pos) {
	assert(pos >= 0 && pos < size);
	return *values[pos];
}

template <typename T>
DynamicVector<T>::~DynamicVector() {
	for (int i = 0; i < size; ++i) {
		delete values[i];
	}
	delete[] values;
}

template <typename T>
void DynamicVector<T>::add(const T& element) {
	if (size == capacity) {
		resize();
	}
	values[size] = element.clone();
	size++;
}

template <typename T>
int DynamicVector<T>::getSize() const {
	return size;
}

template <typename T>
const T& DynamicVector<T>::operator[](int pos) const {
	assert(pos >= 0 && pos < size);
	return *values[pos];
}
