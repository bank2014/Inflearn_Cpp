#pragma once
#include "Container.h"

template <class T>
struct Node {
  T* data;
  Node* next;
  Node* prev;

public:
  Node(T* data) : data(data), next(nullptr), prev(nullptr) {}
  virtual ~Node() {
    next = nullptr;
    prev = nullptr;
    delete data;
  }

public:
  bool operator==(const Node& other) const {
    return this == &other;
  }
  Node* operator++() const {
    return this->next;
  }
  Node* operator--() const {
    return this->prev;
  }
};

template <class T>
class LinkedList : public Container<T> {
public:
  uint32	size;
  Node<T>*  head;
  Node<T>*  tail;

public:
  LinkedList() : size(0), head(nullptr), tail(nullptr) {}
  ~LinkedList();

  void			Pushback(T& data);
  void			Pushfront(T& data);
  uint32		Find(T& _data);

  bool			Delete(uint32 index);

  void			Clear();
  Node<T>* operator[](const uint32 index);

  LinkedListIterator<T>* GetIterator() override {
    return new LinkedListIterator<T>(head);
  }
};

template<class T>
inline LinkedList<T>::~LinkedList()
{
  Clear();
}

template<class T>
inline void LinkedList<T>::Pushback(T& data)
{
  Node<T>* newNode = new Node<T>(&data);

  if (!head) {
    head = tail = newNode;
  }
  else {
    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;
  }
  ++size;
}

template<class T>
inline void LinkedList<T>::Pushfront(T& data)
{
  Node<T>* newNode = new Node<T>(&data);

  if (!head) {
    head = tail = newNode;
  }
  else {
    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;
  }
  ++size;
}

template <class T>
inline uint32 LinkedList<T>::Find(T& _data) {
  for (decltype(size) index = 0; index < size; ++index) {
    if ((*this)[index]->data == _data)
      return index;
  }
  return -1;
}

template<class T>
inline bool LinkedList<T>::Delete(uint32 index) {
  if (index < 0 || size <= index) {
    return error;
  }

  Node<T>* targetNode = (*this)[index];

  if (targetNode == head && targetNode == tail) {
    delete targetNode;
    head = nullptr;
    tail = nullptr;
  }
  else if (targetNode == head) {
    targetNode->next->prev = nullptr;
    head = targetNode->next;
    delete targetNode;
  }
  else if (targetNode == tail) {
    targetNode->prev->next = nullptr;
    tail = targetNode->prev;
    delete targetNode;
  }
  else {
    targetNode->prev->next = targetNode->next;
    targetNode->next->prev = targetNode->prev;
    delete targetNode;
  }
  --size;
  return success;
}

template<class T>
inline void LinkedList<T>::Clear() {
  Node<T>* current = head;

  while (current) {
    Node<T>* nextNode = current->next;
    delete current;
    head->next = nextNode;
    current = nextNode;
  }
  size = 0;
  head = nullptr;
  tail = nullptr;
}

template<class T>
Node<T>* LinkedList<T>::operator[](const uint32 index) {
  if (size <= index) {
    return nullptr;
  }
  Node<T>* targetNode = head;
  for (uint32 i = 0; i < index; ++i) {
    targetNode = targetNode->next;
  }
  return targetNode;
}
