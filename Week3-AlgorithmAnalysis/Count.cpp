#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;
void foo(vector<unsigned> &array);

int main(int argc, char **argv)
{
  // Wrong input handling
  if (argc != 2)
  {
    cerr << "Usage: " << argv[0]
         << " n where n is the number of values to use"
         << endl;
    return 1;
  }

  // Setup the value vector and random generator
  vector<unsigned> values;

  // Accept from input to get the number of values that needs to generate
  unsigned number_of_values = static_cast<unsigned>(stoul(argv[1]));

  for (unsigned value = 0; value < number_of_values; value++)
  {
    //values.push_back(10);
  }

  values.push_back(10);
  values.push_back(9);
  values.push_back(8);
  values.push_back(7);
  values.push_back(6);
  values.push_back(5);
  values.push_back(4);
  values.push_back(3);
  values.push_back(2);
  values.push_back(1);

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
  unsigned count = 0;
  size_t array_size = array.size();
  for (size_t start = 0; start < array_size - 1; start++)
  {
    unsigned item = array.at(start);
    size_t position = start;
    while (item == array.at(position))
    {
      position++;
      count++;
    }
  }
  cerr << array_size << " " << count << endl;
}
