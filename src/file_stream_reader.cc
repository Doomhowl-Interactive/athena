#include "minerva/file_stream_reader.hh"
#include "minerva/exceptions.hh"

namespace minerva
{
// TODO file stream is good check!
FileStreamReader::FileStreamReader(std::filesystem::path &path) : m_path(path)
{
    m_stream = std::ifstream(path, std::ifstream::in | std::ifstream::binary);

    if (!m_stream.good())
        throw BadStreamException("reader stream was bad!");
    if (!m_stream.is_open())
        throw BadStreamException("reader stream was not open!");
    if (!std::filesystem::file_size(path))
        throw BadStreamException("m_stream filesize was 0! (check if file is open somewhere else in program!)");
    size_t size = std::filesystem::file_size(path);

    char *data = (char *)malloc(size);
    m_stream.read(data, size);

    CompressedBuffer compressedSections{data,
                                        size}; // all compressed sections are compressed togheter in a single buffer;

    Buffer sectionsBuffer = compressedSections.decompress();
    m_compressedSections = sectionsBuffer.readArray<CompressedBuffer>();
    m_sections.resize(m_compressedSections.size(), nullptr);
}
FileStreamReader::~FileStreamReader()
{
    for (Buffer *ptr : m_sections)
        if (ptr)
            delete ptr;
}
bool FileStreamReader::isStreamGood() const
{
    return m_stream.good();
}
void FileStreamReader::setSectionPointerPosition(size_t index)
{
    m_sections[m_sectionIndex]->setPointerPosition(index);
}
void FileStreamReader::setStreamPosition(size_t index)
{
    if (index < 0 || index > m_sections.size())
        throw IndexOutOfBoundsException("streamPosition was out of bounds");
    m_sectionIndex = index;
}
void FileStreamReader::previousStreamSection()
{
    setStreamPosition(m_sectionIndex - 1);
}
void FileStreamReader::nextStreamSection()
{
    setStreamPosition(m_sectionIndex + 1);
}
size_t FileStreamReader::getStreamSectionCount() const
{
    return m_sectionIndex;
}
const char *FileStreamReader::readData(size_t size)
{
    if (m_sections[m_sectionIndex])
        return m_sections[m_sectionIndex]->readData(size);
    m_sections[m_sectionIndex] = &m_compressedSections[m_sectionIndex].decompress();
    return m_sections[m_sectionIndex]->readData(size);
}
} // namespace minerva