/**
 * Program explanation here
 * @author Your Name Here
 * @version Date Last Modified Here
 */

#include <cstdint>
#include <iostream>
#include <string>
using namespace std;

/**
 * documentation here
 */
size_t hashx(const string& key, size_t table_size);

int main()
{
  string word;
  size_t table_size = 235886;
  while (getline(cin, word))
  {
    // do something with the word
    size_t hash_index = hashx(word, table_size);
    cerr <<  hash_index << endl;
  }
  return 0;
}


size_t hashx(const string& key, size_t table_size)
{
  size_t hash_value = 1;
  for (auto character : key)
  {
    hash_value = 43 * hash_value + static_cast<size_t>(character);
  }
  return hash_value % table_size;
}
