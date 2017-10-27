#pragma once
#include "diningPhilosophers.h"
#include <vector>

std::vector<Philosopher> loadPhilosophers();
void assignForks(std::vector<Fork> forks, std::vector<Philosopher> philosophers);
void beginEating(std::vector<Fork> forks);

