// nqueens via direct NP
// Jon Beck

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

/**
 * count diagonal collisions. the queens on a board are represented by
 * an n-tuple where the ith entry of the tuple represents the row
 * position of the queen in the ith column
 * @param perm the n-tuple, a permutation of 0 .. n-1
 * @return the number of diagonal collisions the board that the tuple
 * represents
 */
unsigned get_collisions(const vector<unsigned>& perm);

/**
 * output an ASCII art horizontal line with plus
 * signs where columns will intersect
 * @param cols the number of columns wide the line is
 */
void hr(unsigned cols);

/**
 * print a chessboard to std output
 * @param permutation the vector representing the board
 */
void print_board(const vector<unsigned>& permutation);

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    cout << "Usage: ./" << argv[0] << " n" << endl;
    cout << "       where n is the number of queens to place" << endl;
    cout << "       on an n x n chessboard, with n < 26" << endl;
    return 2;
  }

  unsigned n = static_cast<unsigned>(stoul(argv[1]));
  assert(n < 26);
  srand(static_cast<unsigned>(time(nullptr)));

  vector<unsigned> permutation;
  for (unsigned i = 0; i < n; i++)
  {
    permutation.push_back(i);
  }

  unsigned collisions;
  do
  {
    random_shuffle(permutation.begin(), permutation.end());
    collisions = get_collisions(permutation);
  } while (collisions > 0);

  print_board(permutation);

  return 0;
}

unsigned get_collisions(const vector<unsigned>& perm)
{
  unsigned n = static_cast<unsigned>(perm.size());

  unsigned collisions = 0;
  for (unsigned i = 0; i < n - 1; i++)
  {
    for (unsigned j = i + 1; j < n; j++)
    {
      if (j - i == perm.at(i) - perm.at(j) ||
          j - i == perm.at(j) - perm.at(i))
      {
        collisions++;
      }
    }
  }
  return collisions;
}

void hr(unsigned cols)
{
  cout << "    +";
  for (unsigned col = 0; col < cols; col++)
  {
    cout << "---+";
  }
  cout << endl;
}

void print_board(const vector<unsigned>& permutation)
{
  unsigned n = static_cast<unsigned>(permutation.size());
  hr(n);
  for (unsigned row = 0; row < n; row++)
  {
    cout << ' ' << setw(2) << row << " |";
    for (unsigned col = 0; col < n; col++)
    {
      if (permutation.at(row) == col)
      {
        cout << " X |";
      }
      else
      {
        cout << "   |";
      }
    }
    cout << endl;
    hr(n);
  }

  cout << "     ";
  for (unsigned col = 0; col < n; col++)
  {
    cout << ' ' << static_cast<char>('a' + col) << "  ";
  }
  cout << endl;
}
