/**
 * @file memory.cpp
 * @author Hengyi Li
 * @brief This program is to show the use of the memory
 * @version 0.0.1 Alpha
 * @date 2022-01-19
 * @copyright Copyright (c) 2022 Hengyi Li, All rights reserved.
 */
#include <iostream>

/**
 * @brief This function accept value a and b, b is reference and a is initial to 10
 * @param a is value passing from main and has value 10
 * @param b is reference value passing from main
 * @return uint16_t the value of a + b + c
 */
uint16_t foo(uint16_t a, uint16_t &b);

/**
 * @brief This function modifies x and y
 * @param x is a reference value that multiply by 2
 * @param y is a reference value that add 3
 * This function is void so it does not have any return value
 */
void bar(uint16_t &x, uint16_t &y);

int main()
{
  const uint16_t A_VALUE = 10;
  uint16_t i = 10;
  uint16_t &j = i;
  uint16_t k;
  k = foo(A_VALUE, i);
  std::cout << "i: " << i << std::endl;
  std::cout << "j: " << j << std::endl;
  std::cout << "k: " << k << std::endl;
}

uint16_t foo(uint16_t a, uint16_t &b)
{
  uint16_t c = 20;
  a /= 2;
  b++;
  bar(b,c);
  std::cout << "a: " << a << std::endl;
  std::cout << "b: " << b << std::endl;
  std::cout << "c: " << c << std::endl;
  return a + b + c;
}

void bar(uint16_t &x, uint16_t &y)
{
  x *= 2;
  y += 3;
  std::cout << "x: " << x << std::endl;
  std::cout << "y: " << y << std::endl;
}
