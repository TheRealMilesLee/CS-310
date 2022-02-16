#include <cstdint>
#include <iomanip>
#include <iostream>
#include "pq.h"

using namespace std;

int main()
{

  PriorityQueue pq;

  pq.push(28);
  pq.push(23);
  pq.push(2);
  pq.push(4);
  pq.push(134);
  pq.push(204);
  pq.push(5);
  pq.push(40);
  pq.push(8);
  pq.push(10);
  pq.push(1);
  pq.push(183);

  while (!pq.is_empty())
  {
    cout << pq.pop() << endl;
    }
  uint64_t basic_operations = pq.get_op_count();
  cerr << 12 << ' ' << basic_operations << endl;
  return 0;
}
