#pragma once
#ifndef COMPRESSION_ERROR
#define COMPRESSION_ERROR
#include <core.h>

#include <exception>
#include <iostream>

namespace minerva
{
namespace exceptions
{
class compressionException : public std::runtime_error
{
  public:
    compressionException(const char *error) : std::runtime_error("[minerva] a compression error occured")
    {
        std::cerr << "[Minerva] compression error: " << error << std::endl;
    };
    virtual ~compressionException() {};

  private:
};
} // namespace exceptions
} // namespace minerva
#endif // !COMPRESSION_ERROR
