#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;
int main()
{
  size_t array_size = array.size();  //1
  for (size_t start = 0; start < array_size - 1; start++)
  {
    // 2n
    unsigned item = array.at(start); //1
    size_t position = start; //1
    for (size_t index = start + 1; index < array_size; index++)
    {
      //2n
      if (array.at(index) < item) //1
      {
      }
    }
  }
}
