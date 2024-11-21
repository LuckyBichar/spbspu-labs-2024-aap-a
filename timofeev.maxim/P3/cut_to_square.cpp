#include "cut_to_square.h"
#include <iostream>

int* cut_to_square(const int* matrix, size_t strk, size_t stl)
{
  if (stl <= strk)
  {
    size_t capacity = stl * stl;
    int* new_mtx = nullptr;
    new_mtx = new int[capacity];
    for (size_t i = 0; i < capacity; i++)
    {
      new_mtx[i] = matrix[i];
    }
  }
  return new_mtx;
  else
  {
    size_t capacity = strk * strk;
    int* new_mtx = nullptr;
    new_mtx = new int[capacity];
    size_t ind = 0;
    for (size_t i = 0; i <  strk * stl; i += stl)
    {
      for (size_t j = 0; j < strk; j++)
      {
        new_mtx[ind] = matrix[i + j];
        ind++;
      }
    }
    return new_mtx;
  }
}
