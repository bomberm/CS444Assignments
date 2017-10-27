#pragma once
#include diningPhilosophers.h

std::vector<Philosopher> loadPhilosophers();
void assignForks(std::vector forks, std::vector philosophers);
void beginEating(std::vector forks);

