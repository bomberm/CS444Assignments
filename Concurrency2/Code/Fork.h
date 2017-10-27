#pragma once
#include "diningPhilosophers.h"

class Fork{
  std::unique_lock<std::mutex> inUse;
};

