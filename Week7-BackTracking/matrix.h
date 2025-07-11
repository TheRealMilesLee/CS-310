#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm>
#include <cassert>

/**
 * A generic 2-dimensional array class
 * @author Jon Beck
 * @version 22 October 2019
 */

template <class Object> class Matrix
{
private:
  size_t rows;
  size_t cols;
  Object *data;

public:
  /**
   * @brief Constructor, specifying number of both row and columns
   * @param rows the number of rows
   * @param cols the number of columns
   */
  Matrix(size_t rows, size_t cols);

  /**
   * @brief Access to an element to allow modification
   * @param row the row index
   * @param col the column index
   * @return reference to the element at that position
   */
  Object &at(size_t row, size_t col);

  /**
   * @brief  Constant access to an element
   * @param row the row index
   * @param col the column index
   * @return constant reference to the element at that position
   */
  const Object &at(size_t row, size_t col) const;

  /**
   * @brief Destructor to free allocated memory
   */
  ~Matrix();

  /**
   * @brief Copy constructor to make 1-1 copy of existing matrix
   * @param m the existing matrix to be copied
   */
  Matrix(const Matrix<Object> &m); // Copy constructor

  /**
   * @brief Disallow the rvalue copy constructor
   */
  Matrix(const Matrix<Object> &&m) = delete;

  /**
   * @brief Assignment operator to make 1-1 copy of existing matrix
   * @param m the existing matrix to be copied
   */
  Matrix &operator=(const Matrix<Object> &m); // Assignment operator

  /**
   * @brief Disallow the rvalue assignment operator
   */
  Matrix &operator=(const Matrix<Object> &&m) = delete;

  /**
   * @brief Accessor to determine how many rows are in the matrix
   * @return the number of rows in the matrix
   */
  size_t numrows() const;

  /**
   * @brief Accessor to determine how many columns are in the matrix
   * @return the number of columns in the matrix
   */
  size_t numcols() const;
};

template <class Object>
Matrix<Object>::Matrix(size_t param_rows, size_t param_cols)
  : rows(param_rows), cols(param_cols)
{
  data = new Object[rows * cols];
}

template <class Object>
Matrix<Object>::Matrix(const Matrix<Object> &rhs)
    : rows(rhs.rows), cols(rhs.cols)
{
  data = new Object[rows * cols];
  copy(rhs.data, rhs.data + rows * cols, data);
}

template <class Object>
Matrix<Object> &Matrix<Object>::operator=(const Matrix<Object> &rhs)
{
  assert(rows == rhs.rows && cols == rhs.cols);
  copy(rhs.data, rhs.data + rows * cols, data);
  return *this;
}

template <class Object> Matrix<Object>::~Matrix() { delete[] data; }

template <class Object> Object &Matrix<Object>::at(size_t row, size_t col)
{
  assert(row < rows);
  assert(col < cols);
  return data[cols * row + col];
}


/**
 * @brief This function is a template that return a matrix
 * @tparam Object is the matrix object
 * @param row is the row of the matrix
 * @param col is the column of the matrix
 * @return const Object& is the matrix object
 */
template <class Object>
const Object &Matrix<Object>::at(size_t row, size_t col) const
{
  assert(row < rows);
  assert(col < cols);
  return data[cols * row + col];
}

/**
 * This funcntion is a template that returns the rows
 */
template <class Object> size_t Matrix<Object>::numrows() const
{
  return rows;
}

/**
 * This function is a template that returns columns
 */
template <class Object> size_t Matrix<Object>::numcols() const
{
  return cols;
}
#endif
