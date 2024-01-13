#pragma once
#include "Iterator.h"
#include "LinkedList.h"

template <class T>
class LinkedListIterator : public Iterator<T>
{
private:
  Node<T>* current;

public:
  LinkedListIterator(Node<T>* startNode) : current(startNode) {}

  bool HasNext() override {
    return current->next != nullptr;
  }

  void Next() override {
    current = current->next;
  }
};

