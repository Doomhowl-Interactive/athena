#pragma once
#ifndef COMPRESSION_ERROR
#define COMPRESSION_ERROR
#include <core.h>

#include <exception>
#include <iostream>

namespace athena
{
	namespace exceptions 
	{
		class compressionException : public std::runtime_error
		{
		public:
			compressionException(const char* error) : std::runtime_error("[athena] a compression error occured")
			{
				std::cerr << "[Athena] compression error: " << error << std::endl;
			};
			virtual ~compressionException() {};

		private:

		};
	}
}
#endif // !COMPRESSION_ERROR
