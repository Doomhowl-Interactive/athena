#pragma once
#include "compressed_buffer.hh"

namespace minerva
{
/**
 * @brief This is the interface for all streamWriters
 * sections is the collection of uncompressed minerva::buffer objects to write to!
 * when the streamWriter is flushed all of them get transformed into minerva::compressedBuffer objects.
 */
class streamWriter
{
  public:
    virtual ~streamWriter() = default;
    virtual bool isStreamGood() const = 0;
    virtual void setSectionPointerPosition(size_t index) = 0;
    virtual void setStreamPosition(size_t index) = 0;
    virtual void previousStreamSection() = 0;
    virtual void nextStreamSection() = 0;
    virtual size_t getStreamSectionCount() const = 0;
    virtual void writeData(const char *data, size_t size) = 0;

    template <typename T> void writeObject(const T &object) {};
    template <typename T> void writeArray(const std::vector<T> &vector) {};

    operator bool() const
    {
        return isStreamGood();
    }
    
    virtual compressedBuffer flush() = 0;
};
} // namespace minerva
