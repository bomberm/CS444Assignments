#include "diningPhilosophers.h"

int main(void)
{

  std::vector<Fork> forks;
  std::vector<Philosopher> philosophers = loadPhilosophers();
  
  assignForks(forks, philosophers);

  beginEating(forks);

  while(1);
}

Philosopher::Philosopher(string myName, which hand)
{
  name = myName;
  handedness = hand;
};

std::vector loadPhilosophers()
{

  std::vector<Philosopher> philosophers;
  
