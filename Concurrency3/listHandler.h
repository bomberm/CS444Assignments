#include <forward_list>
#include <iostream> 


enum triStateSuccess
{
  case blocked = (-1);
  case notFound = 0;
  case found = 1;
};

class ListHanlder
{

public:
  ListManager();
  ~ListManager();
  bool insert(int num);
  triStateSuccess remove(int num);
  triStateSuccess search(int num);
  bool isInserting();
  bool isDeleting();
  int numSearchers();

private:
  std::forward_list<int> list;
  bool inserting;
  bool deleting;
  int searchers;
}

