/**
 * @file algorithm_analysis.cpp
 * @author Hengyi Li
 * @brief This file is to sort an unordered array
 * @version 0.3.1
 * @date 2022-01-29
 * @copyright Copyright (c) 2022. Hengyi Li, All rights reserved.
 */
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <string>

using namespace std;

/**
 * @brief This function is to sort the unordered array by
 * 1. Select the number S which is the number in current index
 *    a. Store that select number into a local variable named item
 * 2. Loop through the array
 *    a. Find the first exists number N that is smaller than S
 *    b. Save the index of S into local variable named position
 * 3. Exchange the value
 *    a. call swap to replace the value at index of S by N
 *    b. reset the position, replace the value at index of N by S
 * 4. Increment the index to find the next one.
 * @param array is the reference of unsorted array
 * @return the number of the basic operations performed
 */
unsigned foo(vector<unsigned> &array);

int main(int argc, char **argv)
{
  // Wrong input handling
  if (argc != 2)
  {
    cerr << "Usage: "
          << argv[0]
          << " n where n is the number of values to use"
          << endl;
    return 1;
  }

  // Setup the value vector and random generator
  vector<unsigned> values;
  default_random_engine get_next_value(static_cast<unsigned>
    (chrono::system_clock::now().time_since_epoch().count()));
  uniform_int_distribution<unsigned> generator(0, 999999);

  // Accept from input to get the number of values that needs to generate
  unsigned number_of_values = static_cast<unsigned>(stoul(argv[1]));

  for (unsigned value = 0; value < number_of_values; value++)
  {
    values.push_back(generator(get_next_value));
  }

  unsigned operations_total = foo(values);
  cerr << argv[1] << " " << operations_total << endl;

  for (auto current_value : values) {
    cout << current_value << ' ';
  }
  cout << endl;
  return 0;
}

unsigned foo(vector<unsigned> &array)
{
  unsigned operation_count = 0;
  size_t array_size = array.size();
  operation_count++; // array size assignment
  for (size_t start = 0; start < array_size - 1; start++)
  {
    operation_count += 2; // for loop header
    unsigned item = array.at(start);
    operation_count++; // value at index assignment
    size_t position = start;
    operation_count++; // index assignment to current position
    for (size_t index = start + 1; index < array_size; index++)
    {
      operation_count += 2; // for loop header
      if (array.at(index) < item)
      {
        operation_count++; // value comparison
        position++;
        operation_count++; // position index increment
      }
    }

    if (position != start)
    {
      operation_count++; // index comparison
      while (item == array.at(position))
      {
        operation_count++; // value comparison
        position++;
        operation_count++; // position index increment
      }
      swap(array.at(position), item);
      operation_count += 2; // value swap
      while (position != start)
      {
        operation_count++; // while loop header
        position = start;
        operation_count++; // position index assignment
        for (size_t index = start + 1; index < array_size; index++)
        {
          operation_count += 2; // for loop header
          if (array.at(index) < item)
          {
            operation_count++; // value comparison
            position++;
            operation_count++; // position index increment
          }
        }
        while (item == array.at(position))
        {
          operation_count++; // while loop header
          position++;
          operation_count++; // position index increment
        }
        swap(array.at(position), item);
        operation_count += 2; // value swap
      }
    }
  }
  return operation_count;
}
