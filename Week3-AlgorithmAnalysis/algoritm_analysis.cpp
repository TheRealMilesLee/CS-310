/**
 * @file algorithm_analysis.cpp
 * @author Hengyi Li
 * @brief This file is to
 * @version 0.1
 * @date 2022-01-27
 * @copyright Copyright (c) 2022. Hengyi Li, All rights reserved.
 */
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

/**
 * The purpose of foo here
 * @param array write stuff here
 */
void foo(vector<unsigned> &array);

int main(int argc, char **argv)
{
  // Wrong input handling
  if (argc != 2)
  {
    cerr << "Usage: " << argv[0] << " n where n is the number of values to use" << endl;
    return 1;
  }

  // Setup the value vector and random generator
  vector<unsigned> values;
  default_random_engine get_next_value(static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count()));
  uniform_int_distribution<unsigned> generator(0, 999999);

  unsigned number_of_values = static_cast<unsigned>(stoul(argv[1]));

  for (unsigned value = 0; value < number_of_values; value++)
  {
    values.push_back(generator(get_next_value));
  }

  foo(values);

  for (auto v : values)
  {
    cout << v << ' ';
  }
  cout << endl;
  return 0;
}

void foo(vector<unsigned> &array)
{
  size_t array_size = array.size();

  for (size_t start = 0; start < array_size - 1; start++)
  {
    unsigned item = array.at(start);
    size_t position = start;

    for (size_t index = start + 1; index < array_size; index++)
    {
      if (array.at(index) < item)
      {
        position++;
      }
    }

    if (position != start)
    {
      while (item == array.at(position))
      {
        position++;
      }
      swap(array.at(position), item);

      while (position != start)
      {
        position = start;
        for (size_t index = start + 1; index < array_size; index++)
        {
          if (array.at(index) < item)
          {
            position++;
          }
        }

        while (item == array.at(position))
        {
          position++;
        }
        swap(array.at(position), item);
      }
    }
  }
}