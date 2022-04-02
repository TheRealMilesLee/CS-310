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
 * dump the memo table to standard output
 * @param memo the memo table
 * @param s the first string
 * @param t the second string
 */
void print_memo(const Matrix<int> &memo, const string &s, const string &t);

int main(int argc, char **argv)
{
  if (argc != 6)
  {
    cerr << "Usage: " << argv[0] << " s1 s2 match mismatch gap" << endl;
    return 1;
  }

  // add a space to the beginning of each string to allow traceback
  string s = argv[1];
  s = ' ' + s;
  string t = argv[2];
  t = ' ' + t;

  int match = stoi(argv[3]);
  int mismatch = stoi(argv[4]);
  int gap = stoi(argv[5]);

  cout << "match: " << match << endl;
  cout << "mismatch: " << mismatch << endl;
  cout << "gap: " << gap << endl;

  Matrix<int> memo(s.size() + 1, t.size() + 1);
  for (size_t row = 0; row <= s.size(); row++)
  {
    for (size_t col = 0; col <= t.size(); col++)
    {
      memo.at(row, col) = INT_MAX;
    }
  }

  int score =
      opt(s, s.size() - 1, t, t.size() - 1, memo, match, mismatch, gap);

  cout << "The optimal alignment score between " << s << " and " << t
       << " is " << score << endl;

  cout << endl << "The completed memo table: " << endl << endl;

  print_memo(memo, s, t);

  traceback(memo, s, t, gap);
  return 0;
}

void print_memo(const Matrix<int> &memo, const string &s, const string &t)
{
  int field_width = 6;
  int left_label_width = 6;
  int left_index_width = 3;

  cout << right << setw(left_label_width) << ' ';
  for (size_t col = 0; col < t.size(); col++)
  {
    cout << setw(field_width) << t.at(col);
  }
  cout << endl;

  cout << setw(left_label_width) << ' ';
  for (size_t col = 0; col < t.size(); col++)
  {
    cout << setw(field_width) << col;
  }
  cout << endl;

  cout << setw(left_label_width) << '+';
  for (size_t col = 0; col < t.size(); col++)
  {
    cout << setw(field_width) << "---";
  }
  cout << endl;

  for (size_t row = 0; row < s.size(); row++)
  {
    cout << s.at(row) << setw(left_index_width) << row << " |";
    for (size_t col = 0; col < t.size(); col++)
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

}

int opt(const string &first_string, size_t index_string_1,
        const string &second_string, size_t index_string_2,
        Matrix<int> &memo_table, int match, int mismatch, int gap)
{

}
