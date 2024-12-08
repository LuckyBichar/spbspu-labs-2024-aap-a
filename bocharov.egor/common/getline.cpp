#include "getline.h"
#include <stdexcept>
#include <cstring>
char * bocharov::extend_string(const char * string, std::size_t capacity)
{
  if (capacity <= strlen(string))
  {
    throw std::invalid_argument("Capacity must be greater than the string length");
  }
  char * newString = new char[capacity];
  char * j = newString;
  for (const char * i = string; *i != '\0'; ++i, ++j)
  {
    *j = *i;
  }
  *j = '\0';
  return newString;
}

char * bocharov::getline(std::istream & in, char symbol)
{
  std::size_t capacity = 32;
  char * string = new char[capacity];
  std::size_t string_index = 0;
  std::noskipws(in);
  while ((in >> symbol) && (symbol != '\n'))
  {
    if (string_index == capacity - 1)
    {
      string[string_index] = '\0';
      char * extended_string = nullptr;
      try
      {
        extended_string = extend_string(string, capacity *= 2);
      }
      catch (const std::bad_alloc & e)
      {
        delete[] string;
        std::skipws(in);
        throw;
      }
      delete[] string;
      string = extended_string;
    }
    string[string_index++] = symbol;
  }
  std::skipws(in);
  string[string_index] = '\0';
  return string;
}