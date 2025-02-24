#include "minerva/compressed_buffer.hh"
#include "minerva/exceptions.hh"

#define LZ4F_HEAPMODE 1
#include <lz4frame.h>

namespace minerva
{

CompressedBuffer::CompressedBuffer(Buffer Buffer)
{
    LZ4F_preferences_t preferences{};
    preferences.compressionLevel = LZ4F_compressionLevel_max();
    preferences.frameInfo = LZ4F_INIT_FRAMEINFO;
    preferences.frameInfo.contentSize = Buffer.size();
    preferences.frameInfo.contentChecksumFlag = LZ4F_contentChecksumEnabled;

    m_data.resize(LZ4F_compressBound(Buffer.size(), &preferences));

    size_t size = LZ4F_compressFrame(m_data.data(), m_data.size(), Buffer.data(), Buffer.size(), &preferences);

    if (LZ4F_isError(size))
        throw CompressionException(LZ4F_getErrorName(size));

    m_data.resize(size);
}

CompressedBuffer::CompressedBuffer(const char *data, size_t size)
{
    writeData(data, size);
}

size_t CompressedBuffer::size() const
{
    return m_data.size();
}

const char *CompressedBuffer::data()
{
    return (const char *)m_data.data();
}

size_t CompressedBuffer::contentSize()
{
    LZ4F_dctx *p_compressionContext = nullptr;
    LZ4F_createDecompressionContext(&p_compressionContext, LZ4F_getVersion());

    LZ4F_frameInfo_t frameInfo = LZ4F_INIT_FRAMEINFO;

    size_t srcSize = size();
    LZ4F_getFrameInfo(p_compressionContext, &frameInfo, m_data.data(), &srcSize);

    return frameInfo.contentSize;
}

Buffer &CompressedBuffer::decompress()
{
    if (!m_data.size())
        throw CompressionException("m_data.size() was 0!");
    LZ4F_dctx *p_compressionContext = nullptr;
    LZ4F_createDecompressionContext(&p_compressionContext, LZ4F_getVersion());

    size_t dstSize = contentSize();
    void *dstBuffer = malloc(dstSize);

    size_t srcSize = size();
    LZ4F_errorCode_t error = LZ4F_decompress(p_compressionContext, dstBuffer, &dstSize, data(), &srcSize, nullptr);

    if (LZ4F_isError(error))
        throw CompressionException(LZ4F_getErrorName(error));

    Buffer *p_buffer = new Buffer();
    p_buffer->writeData((const char *)dstBuffer, dstSize);
    return *p_buffer;
}

} // namespace minerva