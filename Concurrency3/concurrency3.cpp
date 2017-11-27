#include <iostream>
#include <thread>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <forward_list>
#include "generalHelpers.h"
#include "sharedResource.h"

void problem1();
void problem2();

int main(void)
{
  std::string input;
  int choice;

  std::cout << "Please select if you would like to see the demonstration of Problem 1 (enter 1) or Problem 2 (enter 2)" << std::endl;

  std::getline(std::cin, input);
  srand(time(NULL));

  while(true)
  {
    std::stringstream(input) >> choice;
    if(1 == choice)
    {
      problem1();
      return 0;
    }
    else if (2 == choice)
    {
      problem2();
      return 0;
    } 
    else
    {
      std::cout << "ERROR: Choice not valid. Please enter 1 for Problem 1 or 2 for Problem 2." << std::endl;
      std::getline(std::cin, input);
    }
  }
}

void problem1()
{
  SharedResource *resource = new SharedResource;
  std::vector<std::thread> threads;
  int sleepTime = (rand() % 3) + 1;
  while(1)
  {
    if(resource->isOverloaded())
    {
      sleep(4); //little pause to make sure system isn't ENTIRELY overwhelmed
    }
    threads.emplace_back(consumeResource, resource);
    threads.back().detach();
    sleep(sleepTime);
    sleepTime = (rand() % 2 ) +1;
  } 
}

void problem2()
{
  std::forward_list<int> *list = new std::forward_list<int>;
  std::vector<std::thread> threads;

  listHandler *list_handler = new listHandler;
  bool deleter_waiting;

  // Spawn processes
  while(1)
  {
    // Check if a deleter is waiting
    deleter_Waiting = list->isDeleting();
    if (deleter_waiting)
    {
      sleep(2);
    }

    int process_choice = (rand() % 100)
    // spawn searcher
    if (process_choice < 40)
        threads.emplace_back(searcher, listHandler, (rand() % 25));

    // spawn inserter
    if (process_choice >= 40 && process_choice < 70)
        threads.emplace_back(inserter, listHandler, (rand() % 25));

    // spawn deleter
    if (process_choice >= 70)
        threads.emplace_back(deleter, listHandler, (rand () % 25));
  }

}
