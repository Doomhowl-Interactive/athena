#include "minerva/file_stream_writer.hh"
#include "minerva/compressed_buffer.hh"
#include "minerva/exceptions.hh"

#include <future>

namespace minerva
{

FileStreamWriter::FileStreamWriter(std::filesystem::path &path) : m_path(path)
{
    m_stream = std::ofstream(path, std::ofstream::out | std::ofstream::binary);

    if (!m_stream.good())
        throw BadStreamException("writer stream was bad!");
    if (!m_stream.is_open())
        throw BadStreamException("writer stream was not open!");

    sections.resize(1);
}
FileStreamWriter::~FileStreamWriter()
{
    m_stream.close();
}
bool FileStreamWriter::isStreamGood() const
{
    return m_stream.good();
}
void FileStreamWriter::setSectionPointerPosition(size_t index)
{
    sections[sectionIndex].setPointerPosition(index);
}
void FileStreamWriter::setStreamPosition(size_t index)
{
    if (index < 0 || index > sections.size())
        throw IndexOutOfBoundsException("streamPosition was out of bounds");
    sectionIndex = index;
}
void FileStreamWriter::previousStreamSection()
{
    sectionIndex = std::max((size_t)0, sectionIndex - 1);
}
void FileStreamWriter::nextStreamSection()
{
    if (sectionIndex + 1 == sections.size())
        sections.push_back(Buffer());

    sectionIndex++;
}
size_t FileStreamWriter::getStreamSectionCount() const
{
    return sections.size();
}
void FileStreamWriter::writeData(const char *data, size_t size)
{
    sections[sectionIndex].writeData(data, size);
}
CompressedBuffer FileStreamWriter::flush()
{
    std::vector<std::future<minerva::CompressedBuffer>> compressedBufferFutures;
    // TODO flush logic (compress all sections and write to buffer and recompress insid final frame!)
    //  Compress each buffer in a separate thread
    for (const auto &section : sections)
    {
        compressedBufferFutures.push_back(std::async(std::launch::async, [&section]() {
            return minerva::CompressedBuffer{section}; // Compress buffer
        }));
    }

    std::vector<CompressedBuffer> compressedSections;
    // Collect the compressed buffers.
    for (auto &future : compressedBufferFutures)
        compressedSections.push_back(future.get());

    minerva::Buffer sectionsBuffer;
    sectionsBuffer.writeArray(compressedSections);

    minerva::CompressedBuffer sectionsCompressedBuffer{sectionsBuffer};

    m_stream.write(sectionsCompressedBuffer.data(), sectionsCompressedBuffer.size());
    return sectionsCompressedBuffer;
}
} // namespace minerva