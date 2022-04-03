/**
 * calculate the optimum alignment between two strings
 * @author your name here
 * @version the date here
 */
#include "matrix.h"
#include <climits>
#include <iomanip>
#include <iostream>
using namespace std;

/**
 * @brief This is the recursive, memoized optimum function for computing the
 * edit distance between two strings
 * @param first_string is the first string
 * @param index_string_1 is the index of the first string
 * @param second_string is the second string
 * @param index_string_2 is the index of the second string
 * @param memo_table is the memo table
 * @param match is the match reward
 * @param mismatch is the mismatch penalty
 * @param gap is the gap penalty
 * @return int is the optimal alignment score of the two strings
 */
int opt(const string &first_string, size_t index_string_1,
        const string &second_string, size_t index_string_2,
        Matrix<int> &memo_table, int match, int mismatch, int gap);

/**
 * @brief This is the traceback to find and print the optimal alignment of
 * the two strings
 * @param memo is the memo table
 * @param first_string is the first string
 * @param second_string is the second string
 * @param gap is the gap penalty
 */
void traceback(const Matrix<int> &memo, const string &first_string,
               const string &second_string, int gap);

/**
 * @brief  This function is to dump the memo table to standard output
 * @param memo the memo table
 * @param first_string the first string
 * @param second_string the second string
 */
void print_memo(const Matrix<int> &memo, const string &first_string,
                const string &second_string);

int main(int argc, char **argv)
{
  // Empty input handling
  if (argc != 6)
  {
    cerr << "Usage: " << argv[0] << " s1 s2 match mismatch gap" << endl;
    return 1;
  }

  // Add a space to the beginning of each string to allow traceback
  string first_string = argv[1];
  first_string = ' ' + first_string;
  string second_string = argv[2];
  second_string = ' ' + second_string;

  // Get each reward and penalty value from the user input
  int match = stoi(argv[3]);
  int mismatch = stoi(argv[4]);
  int gap = stoi(argv[5]);

  // Display the reward and penalty value
  cout << "match: " << match << endl;
  cout << "mismatch: " << mismatch << endl;
  cout << "gap: " << gap << endl;

  // Create the memo table with rowsize = second_string+1, column_size =
  // first_string+1
  Matrix<int> memo(first_string.size() + 1, second_string.size() + 1);

  // Initialize the table as infinity.
  for (size_t row = 0; row <= first_string.size(); row++)
  {
    for (size_t col = 0; col <= second_string.size(); col++)
    {
      memo.at(row, col) = INT_MAX;
    }
  }

  // Get the optimal alignment score, which is in the down right index of the
  // table
  int score = opt(first_string, first_string.size() - 1, second_string,
                  second_string.size() - 1, memo, match, mismatch, gap);

  cout << "The optimal alignment score between" << first_string << " and"
          << second_string << " is " << score << endl;

  cout << endl << "The completed memo table: " << endl << endl;

  // Display the memo table
  print_memo(memo, first_string, second_string);

  // DIsplay how two strings are aligned
  traceback(memo, first_string, second_string, gap);
  return 0;
}

void print_memo(const Matrix<int> &memo, const string &first_string,
                const string &second_string)
{
  int field_width = 6;
  int left_label_width = 6;
  int left_index_width = 3;

  cout << right << setw(left_label_width) << ' ';
  for (size_t col = 0; col < second_string.size(); col++)
  {
    cout << setw(field_width) << second_string.at(col);
  }
  cout << endl;

  cout << setw(left_label_width) << ' ';
  for (size_t col = 0; col < second_string.size(); col++)
  {
    cout << setw(field_width) << col;
  }
  cout << endl;

  cout << setw(left_label_width) << '+';
  for (size_t col = 0; col < second_string.size(); col++)
  {
    cout << setw(field_width) << "---";
  }
  cout << endl;

  for (size_t row = 0; row < first_string.size(); row++)
  {
    cout << first_string.at(row) << setw(left_index_width) << row << " |";
    for (size_t col = 0; col < second_string.size(); col++)
    {
      if (memo.at(row, col) == INT_MAX)
      {
        cout << setw(field_width) << "inf";
      }
      else
      {
        cout << setw(field_width) << memo.at(row, col);
      }
    }
    cout << endl;
  }
}

void traceback(const Matrix<int> &memo, const string &first_string,
               const string &second_string, int gap)
{
  cout << endl << "The aligned strings: " << endl;
  size_t current_row = memo.numrows() - 2;
  size_t current_column = memo.numcols() - 2;
  size_t init_row = 0;
  size_t init_col = 0;

  string align_string_1 = "";
  string align_string_2 = "";
  while (current_row > init_row && current_column > init_col)
  {
    if (memo.at(current_row-1, current_column) == memo.at(current_row, current_column) - gap)
    {
      align_string_1.insert(0, "-");
      align_string_2.insert(0, 1, first_string.at(current_row));
      current_row--;
    }
    else if ( memo.at(current_row, current_column - 1) ==
                  memo.at(current_row, current_column) - gap)
    {
      align_string_1.insert(0, 1, second_string.at(current_column));
      align_string_2.insert(0, "-");
      current_column--;
    }
    else
    {
      align_string_1.insert(0, 1, second_string.at(current_column));
      align_string_2.insert(0, 1, first_string.at(current_row));
      current_row--;
      current_column--;
    }
    cout << current_row << "  :  " << current_column << endl;
  }
  cout << align_string_1 << endl;
  cout << align_string_2 << endl;
}

int opt(const string &first_string, size_t index_string_1,
        const string &second_string, size_t index_string_2,
        Matrix<int> &memo_table, int match, int mismatch, int gap)
{
  int result = 0;
  if (index_string_1 == 0 && index_string_2 == 0)
  {
    memo_table.at(index_string_1, index_string_2) = 0;
  }
  else if (index_string_1 == 0 && index_string_2 != 0)
  {
    if (memo_table.at(index_string_1, index_string_2) == INT_MAX)
    {
      memo_table.at(index_string_1, index_string_2)
        = opt(first_string, index_string_1, second_string, index_string_2 - 1,
                memo_table, match, mismatch, gap) + gap;
    }
  }
  else if (index_string_1 != 0 && index_string_2 == 0)
  {
    if (memo_table.at(index_string_1, index_string_2) == INT_MAX)
    {
      memo_table.at(index_string_1, index_string_2)
        = opt(first_string, index_string_1 - 1, second_string, index_string_2,
              memo_table, match, mismatch, gap) + gap;
    }
  }
  else
  {

    if (memo_table.at(index_string_1, index_string_2) == INT_MAX)
    {
      if (first_string.at(index_string_1) == second_string.at(index_string_2))
      {
        result = opt(first_string, index_string_1 - 1, second_string,
          index_string_2 - 1, memo_table, match, mismatch, gap) + match;
      }
      else
      {
        result = opt(first_string, index_string_1 - 1, second_string,
                     index_string_2 - 1, memo_table, match, mismatch, gap) +
                 mismatch;
      }
      memo_table.at(index_string_1, index_string_2) =
          max(result,
              max(opt(first_string, index_string_1, second_string,
                      index_string_2 - 1, memo_table, match, mismatch, gap) +
                      gap,
                  opt(first_string, index_string_1 - 1, second_string,
                      index_string_2, memo_table, match, mismatch, gap) +
                      gap));
    }
  }
  return memo_table.at(index_string_1, index_string_2);
}
