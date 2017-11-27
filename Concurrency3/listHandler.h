#include <iostream> 
#include <list>
#include <unistd.h>

enum triStateSuccess
{
  blocked = (-1),
  notFound = 0,
  found = 1
};

class ListHandler
{

public:
  ListHandler();
  ~ListHandler();
  bool insert(int num);
  triStateSuccess remove(int num);
  triStateSuccess search(int num);
  bool isInserting();
  bool isDeleting();
  int numSearchers();

private:
  std::list<int> list;
  bool inserting;
  bool deleting;
  int searchers;
};

