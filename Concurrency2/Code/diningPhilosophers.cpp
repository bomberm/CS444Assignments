#include "diningPhilosophers.h"

int sem = 1; 
std::vector<bool> semephorks[5] {0,0,0,0,0};
std::vector<pflag> phil_flags[5] {THINK, THINK, THINK, THINK, THINK};


int main(void)
{

  std::vector<Fork> forks;
  std::vector<Philosopher> philosophers;
  philosophers  = loadPhilosophers();
  
  srand((unsigned)time(0));

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

Philosopher::Philosopher(std::string myName, int i)
{
  name = myName;
  index = i;
};

std::vector<Philosopher> loadPhilosophers()
{
  std::vector<Philosopher> philosophers;
  
  philosophers.push_back(Philosopher("Zeno", 0));
  philosophers.push_back(Philosopher("Boole", 1));
  philosophers.push_back(Philosopher("Nietzsche", 2));
  philosophers.push_back(Philosopher("Zedong", 3));
  philosophers.push_back(Philosopher("Confucius", 4));

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
		UP(semaphorks[i]);
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
	down(semaphorks[i]);
}

void eat(Philosopher thinker)
{
  int wait = (rand()%9)+1);
  std::cout << thinker << " is eating for " << wait << " seconds" << std::endl;
  sleep(wait*1000);

  return;
}

void think(Philosopher thinker)
{
  int wait = (rand()%20)+1;
  std::cout << thinker << " is thinking for " << wait << " seconds" << std::endl;
  sleep(wait*1000);
  
  return;
}
