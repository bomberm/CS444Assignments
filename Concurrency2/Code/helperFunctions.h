#pragma once
#include "diningPhilosophers.h"
#include <vector>

std::vector<Philosopher> loadPhilosophers();
void beginEating(std::vector<Philosopher> forks);
void philosophize(Philosopher thinker);

