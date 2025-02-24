#pragma once
#ifndef INDEX_BOUNDS_EXCEPTION
#define INDEX_BOUNDS_EXCEPTION

#include <core.h>

#include <exception>
#include <iostream>

namespace minerva
{
namespace exceptions
{
class AT_API indexOutOfBoundsException : public std::runtime_error
{
  public:
    indexOutOfBoundsException(const char *msg) : std::runtime_error("[minerva] index was out of bounds!")
    {
        std::cerr << "[Minerva] indexOutOfBoundsException: " << msg << std::endl;
    }
    virtual ~indexOutOfBoundsException() {};

  private:
};

} // namespace exceptions
} // namespace minerva
#endif // !INDEX_BOUNDS_EXCEPTION
