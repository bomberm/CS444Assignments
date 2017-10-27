#include "diningPhilosophers.h"
#include <thread>
#include <mutex>

std::mutex sem_lock;
std::vector<pflag> phil_flags[5];


int main(void)
{

	std::vector<Fork> forks;
	std::vector<Philosopher> philosophers = loadPhilosophers();

	assignForks(forks, philosophers);

	beginEating(forks);

	while (1);
}

Philosopher::Philosopher(string myName, which hand)
{
	name = myName;
	handedness = hand;
};

void down() {
	sem_lock.lock;
}

void up() {
	sem_lock.unlock();
}

std::vector loadPhilosophers()
{

	std::vector<Philosopher> philosophers;

