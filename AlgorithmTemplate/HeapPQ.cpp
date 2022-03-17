class pq
{
private:
  vector<unsigned> unordered_array;
  void bubble_up()
  {
    size_t current_index = size() - 1;
    size_t father_index = (current_index - 1) / 2;
    while (current_index > 0)
    {
      if (array.at(current_index) > array.at(father_index))
      {
        std::swap(array.at(current_index), array.at(father_index));
      }
      current_index = father_index;
      father_index = (father_index - 1) / 2;
    }
  }

  void percolate_down()
  {
    size_t current_index = 0;
    size_t subchild_left = 2 * current_index + 1;
    size_t subchild_right = 2 * current_index + 2;
    bool done = false;
    while (current_index < size() - 1 && subchild_left < size() && subchild_right < size() && !done)
    {
      if (array.at(current_index) < array.at(subchild_left) && array.at(subchild_left) > array.at(subchild_right))
      {
        std::swap(array.at(current_index), array.at(subchild_left));
        current_index = subchild_left;
      }
      if (array.at(current_index) < array.at(subchild_right) && array.at(subchild_right) > array.at(subchild_left))
      {
        std::swap(array.at(current_index), array.at(subchild_right));
        current_index = subchild_right;
      }
      if ((subchild_left == array.size()) || (subchild_left == array.size() - 1))
      {
        done = true;
      }

      if (subchild_right > array.size())
      {
        done = true;
      }
      subchild_left = 2 * current_index + 1;
      subchild_right = 2 * current_index + 2;
    }
  }

public:
  unsigned pop()
  {
    unsigned max;
    max = percolate_down();
    return max;
  }
  void push(unsigned push_value)
  {
    unordered_array.push_back(push_value);
    bubble_up();
  }
  bool isEmpty() { return unordered_array.empty(); }
}
