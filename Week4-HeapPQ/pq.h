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
    op_count += 3;
    size_t current_index = size() - 1;

    size_t last_index = (current_index - 1) / 2;
    while (current_index > 0)
    {
      if (array.at(current_index) > array.at(last_index))
      {
        std::swap(array.at(current_index), array.at(last_index));
      }
      current_index = last_index;
      last_index = (last_index - 1) / 2;
    }
}
  void percolate_down()
  {
    size_t current_index = 0;
    size_t subchild_left = 2 * current_index + 1;
    size_t subchild_right = 2 * current_index + 2;
    while (current_index < size() - 1 && subchild_left < size() && subchild_right < size())
    {
      op_count += 3;
      if (array.at(current_index) < array.at(subchild_left) && array.at(subchild_left) > array.at(subchild_right))
      {
        std::swap(array.at(current_index), array.at(subchild_left));
        current_index = subchild_left;
      }
      else if (array.at(current_index) < array.at(subchild_right) && array.at(subchild_right) > array.at(subchild_left))
      {
        std::swap(array.at(current_index), array.at(subchild_right));
        current_index = subchild_right;
      }
      else
      {
        current_index++;
      }
      subchild_left = 2 * current_index + 1;
      subchild_right = 2 * current_index + 2;
    }
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
  unsigned pop()
  {
    size_t max_position = array.size();
    unsigned max_value = 0;
    for (size_t index = 0; index < array.size(); index++)
    {
      op_count += 2; // for loop header
      if (array.at(index) > max_value)
      {
        max_value = array.at(index);
        max_position = index;
      }
    }
    op_count += 2; // for loop header last time

    assert(max_position != array.size()); // no op_count for sanity check

    for (size_t index = max_position; index < array.size() - 1; index++)
    {
      array.at(index) = array.at(index + 1);
    }
    array.pop_back();
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
