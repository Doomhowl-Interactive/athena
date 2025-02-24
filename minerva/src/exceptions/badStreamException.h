#pragma once
#ifndef BAD_STREAM_EXCEPTION
#define BAD_STREAM_EXCEPTION

#include <exception>
#include <iostream>
namespace minerva
{
namespace exceptions
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
} // namespace exceptions
} // namespace minerva
#endif // !BAD_STREAM_EXCEPTION
