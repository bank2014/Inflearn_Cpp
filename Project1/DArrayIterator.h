#pragma once
#include "Iterator.h"

template <typename T>
class DArrayIterator : public Iterator<T>
{
private:
  T *current;

public:
  DArrayIterator(T* startElement) : current(startElement) {}

  bool HasNext() override {
    return current != nullptr;
  }

  void Next() override {
    current++;
  }
};

