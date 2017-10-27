#include <iostream>
#include <string>
#include <vector>
#include "helperFunctions.h"

enum which{
left, 
right
};

enum pflag {
	THINK,
	HUNGRY,
	EAT
};

class Philosopher{

public:
  Philosopher();
  std::string name;
  Fork *leftFork, *rightFork;
  which handedness; //define which hand reaches first

  bool takeFork(which fork);
  void think();
  void eat();
};

class Fork{
  Philosopher left;
  Philosopher right;

  bool inUse;
};
