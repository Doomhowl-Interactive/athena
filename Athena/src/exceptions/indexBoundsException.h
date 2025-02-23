#pragma once
#ifndef INDEX_BOUNDS_EXCEPTION
#define INDEX_BOUNDS_EXCEPTION

#include <core.h>

#include <exception>
#include <iostream>

namespace athena 
{
	namespace exceptions 
	{
		class AT_API indexOutOfBoundsException : public std::runtime_error
		{
		public:
			indexOutOfBoundsException(const char* msg) : std::runtime_error("[athena] index was out of bounds!")
			{
				std::cerr << "[Athena] indexOutOfBoundsException: " << msg << std::endl;
			}
			virtual ~indexOutOfBoundsException() { };

		private:

		};

	}
}
#endif // !INDEX_BOUNDS_EXCEPTION
