#pragma once
#include "compressed_buffer.hh"
#include "stream_reader.hh"

#include <filesystem>
#include <fstream>
#include <iostream>

namespace minerva
{
class fileStreamReader : public streamReader
{
  public:
    fileStreamReader(std::filesystem::path &path);
    fileStreamReader(const fileStreamReader &) = delete;
    ~fileStreamReader();
    virtual bool isStreamGood() const override;
    virtual void setSectionPointerPosition(size_t index) override;
    virtual void setStreamPosition(size_t index) override;
    virtual void previousStreamSection() override;
    virtual void nextStreamSection() override;
    virtual size_t getStreamSectionCount() const override;
    virtual const char *readData(size_t size) override;
    template <typename T> T readObject()
    {
        if (m_sections[m_sectionIndex])
            return m_sections[m_sectionIndex]->readObject<T>();
        m_sections[m_sectionIndex] = &m_compressedSections[m_sectionIndex].decompress();
        return m_sections[m_sectionIndex]->readObject<T>();
    };
    template <typename T> std::vector<T> &readArray()
    {
        if (m_sections[m_sectionIndex])
            return m_sections[m_sectionIndex]->readArray<T>();
        m_sections[m_sectionIndex] = &m_compressedSections[m_sectionIndex].decompress();
        return m_sections[m_sectionIndex]->readArray<T>();
    };

  private:
    std::filesystem::path m_path;
    std::ifstream m_stream;

    size_t m_sectionIndex = 0;

    std::vector<buffer *> m_sections;
    std::vector<compressedBuffer> m_compressedSections;
};

} // namespace minerva
