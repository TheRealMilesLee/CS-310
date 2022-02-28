void shellsort(vector<unsigned> &array)
{
  size_t n = array.size();
  vector<size_t> gaps{5, 3, 1};

  for (auto gap : gaps)
  {
    for (size_t i = gap; i < n; i++)
    {
      unsigned temp = array.at(i);
      size_t j = i;
      while (j >= gap && temp < array.at(j - gap))
      {
        array.at(j) = array.at(j - gap);
        j -= gap;
      }
      array.at(j) = temp;
    }
  }
}
