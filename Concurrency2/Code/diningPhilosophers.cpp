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

	beginEating(philosophers);

	while (1);
}

void beginEating(std::vector<Philosopher> thinkers)
{
  std::thread first(philosophize, thinkers[0]);
  std::thread second(philosophie, thinkers[1];
  std::thread third(philosophie, thinkers[2];
  std::thread forth(philosophie, thinkers[3];
  std::thread fifth(philosophie, thinkers[4];
  
  sem = 0;

  return;
}

philosophize(Philosopher thinker)
{
  while(1);
  {
    thinker.think();
    if(takeforks(thinker))
    {
      thinker.eat();
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

void 
Philosopher::eat()
{
  int wait = (rand()%9)+1);
  std::cout << name << " is eating for " << wait << " seconds" << std::endl;
  sleep(wait*1000);

  return;
}

void 
Philosopher::think()
{
  int wait = (rand()%20)+1;
  std::cout << name << " is thinking for " << wait << " seconds" << std::endl;
  sleep(wait*1000);
  
  return;
}


