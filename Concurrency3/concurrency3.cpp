#include <iostream>
#include <thread>
#include <sstream>

void problem1();
void problem2();

int main(void)
{
  std::string input;
  int choice;

  std::cout << "Please select if you would like to see the demonstration of Problem 1 (enter 1) or Problem 2 (enter 2)" << std::endl;

  std::getline(std::cin, input);

  while(1)
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

  std::cout << "Foo" << std::endl;
}

void problem2()
{
  std::cout << "Bar" << std::endl;
}
