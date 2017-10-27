#include "diningPhilosophers.h"
#include <thread>
#include <mutex>

int sem = 1; 
std::vector<bool> semephorks[5] {0,0,0,0,0};
std::vector<pflag> phil_flags[5] {THINK, THINK, THINK, THINK, THINK};


int main(void)
{

  std::vector<Fork> forks;
  std::vector<Philosopher> philosophers;
  philosophers  = loadPhilosophers();
  
  assignForks(forks, philosophers);

	beginEating(forks);

	while (1);
}

philosophize(Philosopher thinker)
{
  while(1);
  {
    think(thinker);
    if(takeforks(thinker))
    {
      eat(thinker);
    }
    dropforks(thinker);
  }
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

void down(int s) {
	while (s <= 0) {
		_sleep(1);
	}
	s--;
}

void up(int s) {
	s++;
}

void check_neighbors(int i)
{
	if (phil_flags[i] == HUNGRY    &&    phil_flags[(i + 1) % 5] != EAT    &&    phil_flags[(i - 1) % 5] != EAT) {
		phil_flags[i] == EAT;
		UP(semephorks[i]);
	}
}

void dropforks(int i)
{
	down(sem);
	check_neighbors(i - 1);
	check_neighbors(i + 1);
	up(sem);
}

void takeforks(int i)
{
	down(sem);
	pflag[i] = HUNGRY;
	check_neighbors(i);
	up(sem);
	down(semephorks[i]);
}
