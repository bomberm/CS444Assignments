#include "generalHelpers.h"

void consumeResource(SharedResource *resource)
{

  srand(time(NULL)); //prepare random for use
  int sleepTime;
  int mySlot = resource->use();

  while(mySlot == (-1)) //if resource is fully consumed, it will return -1
  {
    std::cout << "Resource is fully consumed, waiting to try again" << std::endl;
    sleep(1); //wait one second and try again
    mySlot == resource->use();
  }
  
  sleepTime = (rand() % 5) + 1;
  std::cout << "Assigned slot " << mySlot << " using resource for " << sleepTime << " seconds." << std::endl;
  std::cout << resource->numberInUse() << " now in use." << std::endl;
  if(resource->numberInUse() == 3)
  {
    std::cout << "Resource overloaded!" << std::endl;
  }

  sleep(sleepTime);

  resource->release(mySlot);

  std::cout << "Releasing slot " << mySlot << ". This thread is exiting." << std::endl;
  std::cout << resource->numberInUse() << " now in use." << std::endl;
};


void inserter(ListHandler *list, int newElement)
{
  while(list->isInserting || list->isDeleting())
  {
    std::cout << "Waiting for insertion/deletion to complete" << std::endl;
  }

  while(!list->insert(newElement));

  std::cout << "Successfully inserted " << newElement << " onto the list." << std::endl;

}

void searcher(ListHandler *list, int num)
{
  while(list->isDeleting())
  {
    std::cout << "Waiting for deletion." << std::endl;
  }

  auto result = list->search(num);
  while(result == blocked)
  {
    result = list->search(num);
  }

  if(result == notFound)
  {
    std::cout << num << " not found in list." << std::endl;
  }
  else
  {
    std::cout << num << " is in the list!" << std::endl;
  }
}

void deleter(ListHanlder *list, int num)
{

  while(list->isDeleting())
  {
    std::cout << "Waiting for deleter to finish." << std::endl;
  }

  auto result = list->delete(num);
  while(result == blocked)
  {
    std::cout << "Waiting for activity to calm before deleting." << std::endl;
    result = list->delete(num);
  }

  if(result == found)
  {
    std::cout << "Successfully removed " << num << " from the list." << std::endl;
  }
  else
  {
    std::cout << num << " was not on list." <<std::endl;
  }
}
