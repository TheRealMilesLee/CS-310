#include <cstdint>
#include <iomanip>
#include <random>
#include <iostream>
#include "pq.h"

using namespace std;

int main(int argc, char **argv)
{

  PriorityQueue pq;
  // Wrong input handling
  if (argc != 2)
  {
    cerr << "Usage: " << argv[0]
         << " n where n is the number of values to use"
         << endl;
    return 1;
  }

  default_random_engine get_next_value(static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count()));
  uniform_int_distribution<unsigned> generator(0, 999999);

  // Accept from input to get the number of values that needs to generate
  unsigned number_of_values = static_cast<unsigned>(stoul(argv[1]));

  for (unsigned value = 0; value < number_of_values; value++)
  {
    pq.push(generator(get_next_value));
  }
  size_t size = pq.size();
  while (!pq.is_empty())
  {
    cout << " " << pq.pop();
  }
  cout << endl << endl;
  uint64_t basic_operations = pq.get_op_count();
  cerr << size << ' ' << basic_operations << endl;
  return 0;
}
