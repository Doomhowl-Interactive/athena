#pragma once
#include "buffer.hh"
#include "stream_writer.hh"

#include <filesystem>
#include <fstream>
#include <iostream>

namespace minerva
{
class FileStreamWriter : public IStreamWriter
{
  public:
    FileStreamWriter(std::filesystem::path &path);
    FileStreamWriter(const FileStreamWriter &) = delete;

    virtual ~FileStreamWriter();
    virtual bool isStreamGood() const override;
    virtual void setSectionPointerPosition(size_t index) override;
    virtual void setStreamPosition(size_t index) override;
    virtual void previousStreamSection() override;
    virtual void nextStreamSection() override;
    virtual size_t getStreamSectionCount() const override;
    virtual void writeData(const char *data, size_t size) override;

    template <typename T> void writeObject(const T &object)
    {
        sections[sectionIndex].writeObject(object);
    };

    template <typename T> void writeArray(const std::vector<T> &vector)
    {
        sections[sectionIndex].writeArray(vector);
    };

    virtual CompressedBuffer flush();

  private:
    size_t sectionIndex = 0;

    std::filesystem::path m_path;
    std::ofstream m_stream;
    std::vector<Buffer> sections;
};
} // namespace minerva
