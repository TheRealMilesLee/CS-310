class pq
{
private:
  vector<unsigned> unordered_array;
  unsigned search_max()
  {
    unsigned max_number = 0;
    size_t index = 0;
    size_t max_index;
    while (index < unordered_array.size())
    {
      if (max_number < unordered_array.at(index))
      {
        max_number = unordered_array.at(index);
        max_index = index;
      }
      index++;
    }

    while (max_index < unordered_array.size() - 1)
    {
      unordered_array.at(max_index) = unordered_array.at(max_index + 1);
      max_index++;
    }
    unordered_array.pop_back();
    return max_number;
  }
public:
  unsigned pop()
  {
    unsigned max;
    max = search_max();
    return max;
  }
  void push(unsigned push_value)
  {
    unordered_array.push_back(push_value);
  }
  bool isEmpty()
  {
    return unordered_array.empty();
  }
}
