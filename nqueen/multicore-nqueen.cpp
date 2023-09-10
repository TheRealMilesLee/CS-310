#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <atomic>
#include <condition_variable>

using namespace std;

// Global variables
std::mutex mtx;
std::atomic<bool> solution_found(false);
const unsigned MAX_THREADS = 16; // Maximum number of threads to use
std::condition_variable solution_cv;

/**
 * count diagonal collisions. the queens on a board are represented by
 * an n-tuple where the ith entry of the tuple represents the row
 * position of the queen in the ith column
 * @param perm the n-tuple, a permutation of 0 .. n-1
 * @return the number of diagonal collisions the board that the tuple
 * represents
 */
unsigned get_collisions(const vector<unsigned> &perm);

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
void print_board(const vector<unsigned> &permutation);


/**
 * The function `solve_nqueens` recursively solves the N-Queens problem by placing queens on a
 * chessboard and checking for collisions, and prints the first valid solution found.
 *
 * @param permutation The `permutation` parameter is a vector of unsigned integers that represents the
 * current state of the chessboard. Each element in the vector represents the row position of a queen
 * in a particular column. For example, if `permutation[0] = 2`, it means that there is a queen
 * @param n The parameter `n` represents the size of the chessboard and the number of queens to be
 * placed on it.
 * @param col The parameter "col" represents the current column being considered for placing a queen on
 * the chessboard. It starts from 0 and increases until it reaches n-1, where n is the size of the
 * chessboard.
 *
 * @return The function `solve_nqueens` returns a boolean value.
 */
bool solve_nqueens(vector<unsigned> &permutation, unsigned n, unsigned col);

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    cout << "Usage: ./" << argv[0] << " n" << endl;
    cout << "       where n is the number of queens to place" << endl;
    cout << "       on an n x n chessboard, with n < 100" << endl;
    return 2;
  }

  unsigned n = static_cast<unsigned>(stoul(argv[1]));
  assert(n < 100);
  srand(static_cast<unsigned>(time(nullptr)));

  vector<unsigned> permutation(n);
  for (unsigned i = 0; i < n; i++)
  {
    permutation[i] = i;
  }

  vector<thread> threads;
  unsigned num_threads = min(MAX_THREADS, n);

  for (unsigned i = 0; i < num_threads; ++i)
  {
    unsigned col_start = i * n / num_threads;
    unsigned col_end = (i + 1) * n / num_threads;
    threads.emplace_back([&, col_start, col_end]
                         {
      vector<unsigned> local_permutation = permutation;
      solve_nqueens(local_permutation, n, col_start); });
  }

  for (auto &thread : threads)
  {
    thread.join();
  }

  return 0;
}

unsigned get_collisions(const vector<unsigned> &perm)
{
  unsigned n = static_cast<unsigned>(perm.size());

  unsigned collisions = 0;
  for (unsigned i = 0; i < n - 1; i++)
  {
    for (unsigned j = i + 1; j < n; j++)
    {
      if (j - i == perm[i] - perm[j] || j - i == perm[j] - perm[i])
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

void print_board(const vector<unsigned> &permutation)
{
  unsigned n = static_cast<unsigned>(permutation.size());
  hr(n);
  for (unsigned row = 0; row < n; row++)
  {
    cout << ' ' << setw(2) << row << " |";
    for (unsigned col = 0; col < n; col++)
    {
      if (permutation[row] == col)
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

bool is_safe(const vector<unsigned> &permutation, unsigned row, unsigned col)
{
  for (unsigned i = 0; i < col; i++)
  {
    if (permutation[i] == row || abs(static_cast<int>(row - permutation[i])) == static_cast<int>(col - i))
    {
      return false;
    }
  }
  return true;
}


bool solve_nqueens(vector<unsigned> &permutation, unsigned n, unsigned col)
{
  if (col == n)
  {
    unsigned collisions = get_collisions(permutation);
    if (collisions == 0)
    {
      {
        std::lock_guard<std::mutex> lock(mtx);
        if (!solution_found)
        {
          print_board(permutation);
          solution_found = true;
        }
      }
      solution_cv.notify_all();
    }
    return true;
  }

  bool res = false;
  for (unsigned i = 0; i < n; i++)
  {
    if (is_safe(permutation, i, col))
    {
      permutation[col] = i;
      res = solve_nqueens(permutation, n, col + 1) || res;
      permutation[col] = 0; // Reset the position for backtracking
    }
  }
  return res;
}
