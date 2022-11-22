/**
 * @file pq.h
 * @author Hengyi Li
 * @brief   Provide a priority queue based on an unsorted vector.
 * This implementation also provides a field for counting basic operations.
 * @version 0.1.0 Alpha
 * @date 2022-02-15
 * @copyright Copyright (c) 2022. Hengyi Li, All rights reserved
 *
 */
#ifndef MY_PQ
#define MY_PQ

#include <cassert>
#include <cstdint>
#include <climits>
#include <vector>

class PriorityQueue
{
private:
  std::vector<unsigned> array;
  uint64_t op_count;
  void bubble_up()
  {
    // Initial setup, 5 ops in total
    size_t current_index = size() - 1;
    op_count += 2; // minus and assignment
    size_t father_index = (current_index - 1) / 2;
    op_count += 3; // arithmetic and assignment

    while (current_index > 0)
    {
      op_count++; // while header
      op_count += 3; // If compare and array access
      if (array.at(current_index) > array.at(father_index))
      {
        std::swap(array.at(current_index), array.at(father_index));
        op_count += 2; // swap
      }
      current_index = father_index;
      op_count++; // Assignment count
      father_index = (father_index - 1) / 2;
      op_count += 3; // minus, divide and assignment
    }
    op_count++; // while last time
}

  void percolate_down()
  {
    size_t current_index = 0;
    op_count++; //assignment

    size_t subchild_left = 2 * current_index + 1;
    op_count += 3; //arithmetic and assignment

    size_t subchild_right = 2 * current_index + 2;
    op_count += 3;  //arithmetic and assignment

    while (current_index < size() - 1 && subchild_left < size()
              && subchild_right < size())
    {
      op_count += 6; // while header
      op_count += 7; // array access and compare
      if (array.at(current_index) < array.at(subchild_left)
      && array.at(subchild_left) > array.at(subchild_right))
      {
        std::swap(array.at(current_index), array.at(subchild_left));
        op_count += 2; // swap
        current_index = subchild_left;
        op_count++; //assignment
      }
      op_count += 7; // array access and compare
      if (array.at(current_index) < array.at(subchild_right)
        && array.at(subchild_right) > array.at(subchild_left))
      {
        std::swap(array.at(current_index), array.at(subchild_right));
        op_count += 2; // swap
        current_index = subchild_right;
        op_count++; //assignment
      }
      op_count += 17; //else situation
      if (!(array.at(current_index) < array.at(subchild_left)
        && array.at(subchild_left) > array.at(subchild_right))
        &&!((array.at(current_index) < array.at(subchild_right)
        && array.at(subchild_right) > array.at(subchild_left))))
      {
        current_index++;
        op_count++; //increment
      }

      subchild_left = 2 * current_index + 1;
      op_count += 3;  //arithmetic and assignment
      subchild_right = 2 * current_index + 2;
      op_count += 3;  //arithmetic and assignment
    }
    op_count += 6; // while last time
  }

public:
/**
 * @brief Constructor for an empty priority queue
 */
  PriorityQueue() : op_count{0} {}

  /**
   * Insert a priority into the PQ
   * @param priority the priority of the inserted job
   */
  void push(unsigned priority)
  {
    array.push_back(priority);
    op_count++; // one operation for push_back
    bubble_up();
  }

  /**
   * Remove and return the maximum-priority job in the queue.
   * @return the priority of the removed job
   */
  uint64_t pop()
  {
    size_t initial_index = 0;
   op_count++;  //assignment
    uint64_t max_value = array.at(initial_index);
    op_count += 2; //array access and assignment
    array.at(initial_index) = array.at(size() - 1);
    op_count += 4;  //array access and assignment
    array.pop_back();
    op_count++; //one operation for pop_back
    percolate_down();
    return max_value;
  }

  /**
   * Report if the queue is empty
   * @return true if empty, false otherwise
   */
  bool is_empty() const
  {
    return array.empty();
  }

  /**
   * Report the number of elements in the queue
   * @return the number of elements
   */
  size_t size() const
  {
    return array.size();
  }

  /**
   * Return the number of basic operations counted so far
   * @return the count of basic operations
   */
  uint64_t get_op_count() const
  {
    return op_count;
  }
};
#endif
