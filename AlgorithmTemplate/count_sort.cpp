void count_sort (vector<unsigned> &array)
{
  size_t size = array.size();
  vector<unsigned> counts(size, 0);
  for (size_t outer = 0; outer < size-1; outer++)
  {
    for (size_t inner = outer + 1; inner < size; inner++)
    {
      if (array.at(outer) < array.at(inner))
      {
        counts.at(inner)++;
      }
      else
      {
        counts.at(outer)++;
      }
    }
  }

  vector<unsigned> copy = array;
  for (size_t loop = 0; loop < size; loop++)
  {
    array.at(counts.at(loop)) = copy.at(loop);
  }
}
