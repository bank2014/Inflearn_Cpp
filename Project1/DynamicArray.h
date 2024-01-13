#pragma once
#include "Container.h"
#include "DArrayIterator.h"

template <typename T>
class DynamicArray : public Container<T>{
public:
  DynamicArray(uint32 initialCapacity);
  ~DynamicArray();

  void Pushback(T& data);
  void Popback();
  T& operator[](uint32 index);
  void resize(uint32 newSize);

  DArrayIterator<T>* GetIterator() override {
    return new DArrayIterator<T>(arr);
  }

public:
  uint32 capacity;
  uint32 size;
private:
  T* arr;
};

template <typename T>
DynamicArray<T>::DynamicArray(uint32 initialCapacity)
{
  if (initialCapacity < 0) {
    throw std::runtime_error("Invalid initial capacity");
  }
  arr = new T[initialCapacity];
  memset(arr, 0, sizeof(T) * initialCapacity);
  capacity = initialCapacity;
  size = 0;
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
  delete[] arr;
}

template<typename T>
inline void DynamicArray<T>::Pushback(T& data)
{
  if (size == capacity) {
    resize(capacity * 2);
  }
  ++size;
  arr[size - 1] = data;
}

template<typename T>
inline void DynamicArray<T>::Popback()
{
  if (size == 0) {
    throw std::runtime_error("Array is empty");
  }
  --size;
}

template <typename T>
T& DynamicArray<T>::operator[](uint32 index) {
  if (index < 0 || size <= index) {
    throw std::runtime_error("Index out of bounds");
  }
  return arr[index];
}

template <typename T>
void DynamicArray<T>::resize(uint32 newCapacity) {
  if (newCapacity < 0) {
    throw std::runtime_error("Invalid new capacity");
  }
  T* newArr = new T[newCapacity];

  uint32 minCapacity = (capacity < newCapacity) ? capacity : newCapacity;
  size = 0;
  for (uint32 i = 0; i < minCapacity; i++) {
    newArr[i] = arr[i];
    ++size;
  }

  delete[] arr;
  arr = newArr;
  capacity = newCapacity;
}
