#pragma once
#include "buffer.hh"

namespace minerva
{
class CompressedBuffer : protected Buffer
{
  public:
    CompressedBuffer(Buffer Buffer);
    CompressedBuffer(const char *data, size_t size);
    CompressedBuffer() = default;
    size_t size() const;
    const char *data();

    size_t contentSize();
    Buffer &decompress();
    static void serialize(Buffer *p_dstBuffer, const CompressedBuffer &srcBuffer)
    {
        size_t srcSize = srcBuffer.size();

        p_dstBuffer->writeData((const char *)&srcSize, sizeof(size_t));
        p_dstBuffer->writeData((const char *)srcBuffer.m_data.data(), srcBuffer.size());
    }
    static CompressedBuffer &deserialize(minerva::Buffer *p_srcBuffer)
    {
        CompressedBuffer *p_dstBuffer = new CompressedBuffer();

        size_t size = *(size_t *)p_srcBuffer->readData(sizeof(size_t));

        p_dstBuffer->writeData(p_srcBuffer->readData(size), size);

        return *p_dstBuffer;
    }
};
} // namespace minerva
