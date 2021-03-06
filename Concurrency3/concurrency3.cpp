#include <iostream>
#include <thread>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
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
    }
    else if (2 == choice)
    {
      problem2();
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
  std::vector<std::thread> threads;

  ListHandler *list_handler = new ListHandler();

  // Spawn processes
  while(true)
  {
    // Check if a deleter is waiting
    if (list_handler->isDeleting())
    {
      sleep(5);
    }

    int process_choice = (rand() % 100);
    // spawn searcher
    if (process_choice < 40)
        threads.emplace_back(searcher, list_handler, (rand() % 25));

    // spawn inserter
    if (process_choice >= 40 && process_choice < 70)
        threads.emplace_back(inserter, list_handler, (rand() % 25));

    // spawn deleter
    if (process_choice >= 70)
        threads.emplace_back(deleter, list_handler, (rand () % 25));

    threads.back().detach();
    sleep(1);
  }

}
