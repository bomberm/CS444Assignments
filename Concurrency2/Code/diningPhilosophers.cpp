#include "diningPhilosophers.h"

int main(void)
{

  std::vector<Fork> forks;
  std::vector<Philosopher> philosophers = loadPhilosophers();
  
  assignForks(forks, philosophers);

  beginEating(forks);

  while(1);
}

Philosopher::Philosopher()
{

};
std::vector loadPhilosophers()
{

  std::vector<Philosopher> philosophers;
