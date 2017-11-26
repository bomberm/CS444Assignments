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

