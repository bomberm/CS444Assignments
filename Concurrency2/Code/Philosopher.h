#pragma once
#include "Fork.h"
#include "diningPhilosophers.h"


enum which{
left,
right
};

class Philosopher{

public:
  Philosopher(std::string myName, int i);
  std::string name;
  int index; //philosophers location at the table

  void takeForks();
  void think();
  void eat();
  void dropForks();
};

