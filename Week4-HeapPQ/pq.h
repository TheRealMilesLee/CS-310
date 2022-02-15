/**
 * Provide a priority queue based on an unsorted vector.
 * This implementation also provides a field for counting basic operations.
 * @author Your Name
 * @version The date you last modify this code
 */

/**
 * @brief This file provide a priority queue based on an unsorted vector and provides a field for  * counting basic operations
 * @author Hengyi Li
 * @version 0.0.1.23 Alpha
 * @copyright Copyright (c). 2022 Hengyi Li. All rights preserved
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

public:
/**
 * @brief Priority Queue constructor
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
