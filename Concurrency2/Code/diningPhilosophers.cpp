#include "diningPhilosophers.h"

int sem = 1; 
bool semaphorks[5] {false,false,false,false,false};
pflag phil_flags[5] {THINK, THINK, THINK, THINK, THINK};


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
  std::thread second(philosophize, thinkers[1]);
  std::thread third(philosophize, thinkers[2]);
  std::thread forth(philosophize, thinkers[3]);
  std::thread fifth(philosophize, thinkers[4]);
  
  sem = 0;

  return;
}

void philosophize(Philosopher thinker)
{
  while(1)
  {
    thinker.think();
    thinker.takeForks();
    thinker.eat();
    thinker.dropForks();
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
		sleep(1);
	}
	s--;
}

void up(int s) {
	s++;
}

void check_neighbors(int i)
{
	if (phil_flags[i] == HUNGRY    &&    phil_flags[(i + 1) % 5] != EAT    &&    phil_flags[(i - 1) % 5] != EAT) {
		phil_flags[i] = EAT;
		up(semaphorks[i]);
	}
}

void Philosopher::dropForks()
{
	down(sem);
	check_neighbors(index - 1);
	check_neighbors(index + 1);
	up(sem);
}

void Philosopher::takeForks()
{
	down(sem);
	phil_flags[index] = HUNGRY;
	check_neighbors(index);
	up(sem);
	down(semaphorks[index]);
}

void 
Philosopher::eat()
{
  int wait = (rand()%9)+1;
  std::cout << name << " is eating for " << wait << " seconds" << std::endl;
  sleep(wait);

  return;
}

void 
Philosopher::think()
{
  int wait = (rand()%20)+1;
  std::cout << name << " is thinking for " << wait << " seconds" << std::endl;
  sleep(wait);
  
  return;
}


