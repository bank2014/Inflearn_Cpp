#pragma once
class Object
{
public:
  virtual ~Object(){}
  virtual void Init() = 0;
};
