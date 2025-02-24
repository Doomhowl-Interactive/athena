#include <cstdint>
#include <filesystem>
#include <gtest/gtest.h>
#include <minerva/file_stream_reader.hh>
#include <minerva/file_stream_writer.hh>
#include <minerva/serializable_real.hh>

struct StructA
{
    char str[128];
    uint32_t number;
};

struct StructB
{
    uint64_t number;
};

TEST(IntegrationTests, TestSavingAndLoading1)
{
    auto tempFile = std::filesystem::temp_directory_path() / "test.dat";

    auto writer = minerva::FileStreamWriter(tempFile);

    StructA a{.str = "Hello, World!", .number = 42};

    writer.writeObject(a);

    StructB b{.number = 1337};

    writer.writeObject(b);

    writer.flush();

    auto reader = minerva::FileStreamReader(tempFile);

    auto a2 = reader.readObject<StructA>();

    EXPECT_STREQ(a2.str, "Hello, World!");
    EXPECT_EQ(a2.number, 42);

    auto b2 = reader.readObject<StructB>();

    EXPECT_EQ(b2.number, 1337);

    std::filesystem::remove(tempFile);
}