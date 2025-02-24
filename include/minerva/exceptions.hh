#pragma once
#include <iostream>
#include <stdexcept>

namespace minerva
{

class badStreamException : public std::runtime_error
{
  public:
    badStreamException(const char *error) : std::runtime_error("[minerva] a badStream error occured")
    {
        std::cerr << "[Minerva] badStream error: " << error << std::endl;
    };
    virtual ~badStreamException() {};

  private:
};

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

class indexOutOfBoundsException : public std::runtime_error
{
  public:
    indexOutOfBoundsException(const char *msg) : std::runtime_error("[minerva] index was out of bounds!")
    {
        std::cerr << "[Minerva] indexOutOfBoundsException: " << msg << std::endl;
    }
    virtual ~indexOutOfBoundsException() {};

  private:
};

} // namespace minerva
