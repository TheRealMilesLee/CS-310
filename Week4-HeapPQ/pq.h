/**
 * Provide a priority queue based on an unsorted vector.
 * This implementation also provides a field for counting basic operations.
 * @author Your Name
 * @version The date you last modify this code
 */

#ifndef MY_PQ
#define MY_PQ

#include <cassert>
#include <cstdint>
#include <climits>
#include <vector>

class PriorityQueue
{
public:
  /**
   * Construct an empty priority queue
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

private:
  std::vector<unsigned> array;
  uint64_t op_count;
};
#endif
