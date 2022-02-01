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
#include <string>
#include <vector>

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
 */
void foo(vector<unsigned> &array);

int main(int argc, char **argv)
{
  // Wrong input handling
  if (argc != 2)
  {
    cerr << "Usage: " << argv[0] << " n where n is the number of values to use"
      << endl;
    return 1;
  }

  // Setup the value vector and random generator
  vector<unsigned> values;
  default_random_engine get_next_value(static_cast<unsigned>(
    chrono::system_clock::now().time_since_epoch().count()));
  uniform_int_distribution<unsigned> generator(0, 999999);

  // Accept from input to get the number of values that needs to generate
  unsigned number_of_values = static_cast<unsigned>(stoul(argv[1]));

  for (unsigned value = 1; value < number_of_values; value++)
  {
    values.push_back(generator(get_next_value));
  }


  foo(values);

  for (auto current_value : values)
  {
    cout << current_value << ' ';
  }
  cout << endl;
  return 0;
}

void foo(vector<unsigned> &array)
{
  uint64_t operation_count = 0;
  size_t array_size = array.size();
  operation_count++; // array size assignment

  for (size_t start = 0; start < array_size - 1; start++)
  {
    operation_count += 2; // for loop header

    unsigned item = array.at(start);
    operation_count += 2; // value at index assignment and array access

    size_t position = start;
    operation_count++; // index assignment to current position

    for (size_t index = start + 1; index < array_size; index++)
    {
      operation_count += 2; // for loop header

      operation_count += 2; // if statement comparison and array access
      if (array.at(index) < item)
      {
        position++;
        operation_count++; // position index increment
      }
    }
    operation_count += 2; // for loop last time

    operation_count++; // if statement comparison
    if (position != start)
    {
      while (item == array.at(position))
      {
        operation_count += 2; // while statement compare and array access

        position++;
        operation_count++; // position index increment
      }
      operation_count += 2; // while statement compare and array access

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

          operation_count += 2; // if compare and array access
          if (array.at(index) < item)
          {
            position++;
            operation_count++; // position index increment
          }
        }
        operation_count += 2; // for loop last time

        while (item == array.at(position))
        {
          operation_count += 2; // while compare and array access

          position++;
          operation_count++; // position index increment
        }
        operation_count += 2; // while loop compare and array access last time

        swap(array.at(position), item);
        operation_count += 2; // value swap
      }
      operation_count++; // while loop last time
    }
  }
  operation_count += 2; // for loop last time
  cerr << array_size << " " << operation_count << endl;
}
