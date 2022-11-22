void distribution_sort(vector<size_t> &array, size_t lower, size_t upper)
{
  size_t n = array.size();
  size_t k = upper - lower + 1;
  vector<size_t> counts(k, 0);

  for (size_t loop = 0; loop < n; loop++)
  {
    counts.at(array.at(loop) - lower)++;
  }

  size_t current_value = lower;
  size_t counts_index = 0;
  size_t value_count = 0;
  size_t a_index = 0;

  while (counts_index < k)
  {
    if (value_count < counts.at(counts_index))
    {
      array.at(a_index) = current_value;
      value_count++;
      a_index++;
    }
    else
    {
      counts_index++;
      current_value++;
      value_count = 0;
    }
  }
}
