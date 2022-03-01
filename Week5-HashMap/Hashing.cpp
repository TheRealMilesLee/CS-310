/**
 * @file Hashing.cpp
 * @author Hengyi Li
 * @brief This file is to count the collisions of words in a hash table using
 * hashx function which is to get the index in the hash table.
 * @version 0.2.3.1 alpha
 * @date 2022-03-01
 * @copyright Copyright (c) 2022. Hengyi Li, All rights reserved.
 */
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * @brief  This function is to get the hash index for the input words
 * @param key is the words from input
 * @param table_size is the size of the hash table
 * @return size_t is the index which the hash key corresponds to
 */
size_t hashx(const string& key, size_t table_size);

int main()
{
  string word;
  unsigned count = 0;
  size_t table_size = 102409;
  vector<size_t> all_word_index;
  while (getline(cin, word))
  {
    // Get the hash table index for each words
    size_t hash_index = hashx(word, table_size);
    all_word_index.push_back(hash_index);
  }
  // Sort the vector for easy search
  sort(all_word_index.begin(), all_word_index.end());
  size_t index = 0;
  while (index < all_word_index.size() - 1)
  {
    if (all_word_index.at(index) == all_word_index.at(index + 1))
    {
      count++;
    }
    index++;
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
