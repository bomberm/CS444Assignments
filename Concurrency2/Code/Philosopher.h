#pragma once
#include "Fork.h"
#include "diningPhilosophers.h"


enum which{
left,
right
};

class Philosopher{

public:
  Philosopher(std::string myName);
  std::string name;
  Fork *left, *right;

  bool takeFork(which fork);
  void think();
  void eat();
};

