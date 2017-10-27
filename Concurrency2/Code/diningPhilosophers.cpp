#include "diningPhilosophers.h"
#include <thread>
#include <mutex>

std::mutex sem_lock;
std::vector<pflag> phil_flags[5];


int main(void)
{

  std::vector<Fork> forks;
  std::vector<Philosopher> philosophers;
  philosophers  = loadPhilosophers();
  
  assignForks(forks, philosophers);

	assignForks(forks, philosophers);

	beginEating(forks);

	while (1);
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

void down() {
	sem_lock.lock;
}

void up() {
	sem_lock.unlock();
}

