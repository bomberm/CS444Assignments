#pragma once
#include <iostream>
#include <unistd.h>

class SharedResource
{
  public:
  SharedResource();
  ~SharedResource();

  int use();
  void release(int slot);
  bool isOverloaded();
  int numberInUse();

  private:
  bool available[3]; //three slots to consume, true if not in use
  bool overloaded;
  int usedResources;

};
