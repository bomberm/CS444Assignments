#include "diningPhilosophers.h"

int main(void)
{

  std::vector<Fork> forks;
  std::vector<Philosopher> philosophers;
  philosophers  = loadPhilosophers();
  
  assignForks(forks, philosophers);

  beginEating(forks);

  while(1);
}

Philosopher::Philosopher(std::string myName)
{
  name = myName;
};

std::vector<Philosopher> loadPhilosophers()
{
  std::vector<Philosopher> philosophers;
  
  philosophers.push_back(Philosopher("Zeno"));
  philosophers.push_back(Philosopher("Zedong"));
  philosophers.push_back(Philosopher("Nietzsche"));
  philosophers.push_back(Philosopher("Boole"));
  philosophers.push_back(Philosopher("Confucius"));

  return philosophers;
}

