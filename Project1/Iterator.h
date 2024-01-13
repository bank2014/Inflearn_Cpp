#pragma once

template <typename T>
class Iterator
{
public:
  virtual ~Iterator() {}
  virtual bool HasNext() = 0;
  virtual void Next() = 0;
};

