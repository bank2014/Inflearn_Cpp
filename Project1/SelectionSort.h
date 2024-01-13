#pragma once
#include "DynamicArray.h"
#include "Student.h"

class SelectionSort
{
public:
  static void Sort(DynamicArray<Student*>& arr, uint32 n) {
    for (uint32 i = 0; i < n - 1; ++i) {
      uint32 minIndex = i;
      for (uint32 j = i + 1; j < n; ++j) {
        if (arr[j]->id < arr[minIndex]->id) {
          minIndex = j;
        }
      }
      std::swap(arr[i], arr[minIndex]);
    }
  }
};

