#include "sharedResource.h"

SharedResource::SharedResource()
{
  for(int i=0 ; i < 3 ; i++)
  {
    available[i] = true;
  }

  overloaded = false;
  usedResources = 0;
}

SharedResource::~SharedResource()
{
}

int SharedResource::use()
{
  if(overloaded)
  {
      if(usedResources > 0)
      {
        return (-1);
      }
      else
      {
        overloaded = false;
      }
  }
  if(usedResources < 3)
  {
    for(int i=0; i < 3 ; i++)
    {
      if(available[i])
      {
        available[i] = false;
        usedResources++;
        if( usedResources >= 3)
        {
          overloaded = true;
        }
        return i;
      }
    }
  }
  
  return (-1);
}


void SharedResource::release(int slot)
{

  available[slot] = true;
  usedResources--;
}

bool SharedResource::isOverloaded()
{
  return overloaded;
}

int SharedResource::numberInUse()
{
  return usedResources;
}
