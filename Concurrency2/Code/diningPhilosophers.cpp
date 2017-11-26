#include "diningPhilosophers.h"

int sem = 1; 
bool semaphorks[5] {false,false,false,false,false};
pflag phil_flags[5] {THINK, THINK, THINK, THINK, THINK};
std::mutex sem_lock;


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
  
  sem = 1;

  while (1);

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
		sem_lock.unlock();
		sleep(1);
		sem_lock.lock();
	}
	s--;
}

void up(int s) {
	s++;
}

bool check_neighbors(int i)
{
	bool returnVal = false;
	if (phil_flags[i] == HUNGRY    &&    phil_flags[(i + 1) % 5] != EAT    &&    phil_flags[(i - 1) % 5] != EAT) {
		phil_flags[i] = EAT;
		returnVal = true;
	}
	return returnVal;
}

void Philosopher::dropForks()
{
	sem_lock.lock();
	down(sem);
	sem_lock.unlock();

	semaphorks[index] = false;
	semaphorks[(index + 1) % 5] = false;
	phil_flags[index] = THINK;

	sem_lock.lock();
	up(sem);
	sem_lock.unlock();
}

void Philosopher::takeForks()
{

	phil_flags[index] = HUNGRY;

	bool eating = false;

	while (!eating) {
		sem_lock.lock();
		down(sem);
		sem_lock.unlock();

		eating = check_neighbors(index);

		sem_lock.lock();
		up(sem);
		sem_lock.unlock();
	}

	

	phil_flags[index] = EAT;

	sem_lock.lock();
	semaphorks[index] = true;
	semaphorks[(index + 1) % 5] = true;
	sem_lock.unlock();
}

void 
Philosopher::eat()
{
  int wait = (rand()%9)+1;
  //std::cout << name << " is eating for " << wait << " seconds" << std::endl;
  std::string out = name;
  out.append(" is eating for ");
  out.append(std::to_string(wait) );
  out.append( " seconds\n");
  printf(out.c_str());
  sleep(wait);

  return;
}

void 
Philosopher::think()
{
  int wait = (rand()%20)+1;
  //std::cout << name << " is thinking for " << wait << " seconds" << std::endl;
  std::string out = name;
  out.append(" is thinking for ");
  out.append(std::to_string(wait));
  out.append(" seconds\n");
  printf(out.c_str());
  sleep(wait);
  
  return;
}


