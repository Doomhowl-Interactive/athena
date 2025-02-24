#pragma once
#include <iostream>
#include <stdexcept>

namespace minerva
{

class BadStreamException : public std::runtime_error
{
  public:
    BadStreamException(const char *error) : std::runtime_error("[minerva] a badStream error occured")
    {
        std::cerr << "[Minerva] badStream error: " << error << std::endl;
    };
    virtual ~BadStreamException() {};

  private:
};

class CompressionException : public std::runtime_error
{
  public:
    CompressionException(const char *error) : std::runtime_error("[minerva] a compression error occured")
    {
        std::cerr << "[Minerva] compression error: " << error << std::endl;
    };
    virtual ~CompressionException() {};

  private:
};

class IndexOutOfBoundsException : public std::runtime_error
{
  public:
    IndexOutOfBoundsException(const char *msg) : std::runtime_error("[minerva] index was out of bounds!")
    {
        std::cerr << "[Minerva] IndexOutOfBoundsException: " << msg << std::endl;
    }
    virtual ~IndexOutOfBoundsException() {};

  private:
};

} // namespace minerva
