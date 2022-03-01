/**
 * Program explanation here
 * @author Your Name Here
 * @version Date Last Modified Here
 */

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * documentation here
 */
size_t hashx(const string& key, size_t table_size);

int main()
{
  string word;
  unsigned count = 0;
  size_t table_size = 102401;
  vector<size_t> all_word_index;
  while (getline(cin, word))
  {
    // Get the hash table index for each words
    size_t hash_index = hashx(word, table_size);
    all_word_index.push_back(hash_index);
  }
  sort(all_word_index.begin(), all_word_index.end());
  for (size_t index = 0; index < all_word_index.size() - 1; index++)
  {
    if (all_word_index.at(index) == all_word_index.at(index + 1))
    {
      count++;
    }
  }
  cout << count << endl;
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
