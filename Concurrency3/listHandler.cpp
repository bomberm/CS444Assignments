#include "listHandler.h"

ListHandler::ListHandler()
{
  inserting = false;
  deleting = false;
  searchers = 0;
}

ListHandler::~ListHandler()
{
}

bool ListHandler::insert(int num)
{
  if(inserting || deleting)
  {
    return false;
  }

  inserting = true;
  std::list<int>::iterator iterator;

  list.push_back(num);

  inserting = false;

  return true;
}

triStateSuccess ListHandler::search(int num)
{
  if(deleting)
  {
    return blocked;
  }

  searchers++;

  for( int item : list)
  {
    if( item == num)
    {
      searchers--;
      return found;
    }
  }

  searchers--;
  return notFound;
}

triStateSuccess ListHandler::remove(int num)
{
  if(inserting || searchers > 0)
  {
    return blocked;
  }

  if(search(num) == found)
  {
    deleting = true;
    list.remove(num); 
    deleting = false;
    return found;
  }

  return notFound;
}

bool ListHandler::isInserting()
{
  return inserting;
}

bool ListHandler::isDeleting()
{
  return deleting;
}

int ListHandler::numSearchers()
{
  return searchers;
}
