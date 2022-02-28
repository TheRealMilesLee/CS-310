void shellsort(vector<unsigned> &array)
{
  size_t n = array.size();
  vector<size_t> gaps{5, 3, 1};

  for (auto gap : gaps)
  {
    for (size_t index = gap; index < n; index++)
    {
      unsigned temp = array.at(i);
      size_t jump = index;
      while (jump >= gap && temp < array.at(jump - gap))
      {
        array.at(jump) = array.at(jump - gap);
        jump -= gap;
      }
      array.at(jump) = temp;
    }
  }
}
w
