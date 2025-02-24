#include <cstdint>
#include <ctime>
#include <filesystem>
#include <gtest/gtest.h>
#include <minerva/file_stream_reader.hh>
#include <minerva/file_stream_writer.hh>
#include <minerva/serialized_real.hh>

struct StructA
{
    char str[128];
    uint32_t number;
};

struct StructB
{
    uint64_t number;
    minerva::SerializedReal real;
};

TEST(IntegrationTests, TestSavingAndLoading1)
{
    auto tempFile = std::filesystem::temp_directory_path() / std::format("{}.dat", std::time(nullptr));

    { // do not remove braces: RAII
        auto writer = minerva::FileStreamWriter(tempFile);

        StructA a{.str = "Hello, World!", .number = 42};

        writer.writeObject(a);
        writer.nextStreamSection();

        StructB b{.number = 1337, .real = 3.14159265359};

        writer.writeObject(b);

        writer.flush();
    }

    {
        auto reader = minerva::FileStreamReader(tempFile);

        auto a2 = reader.readObject<StructA>();

        EXPECT_STREQ(a2.str, "Hello, World!");
        EXPECT_EQ(a2.number, 42);

        reader.nextStreamSection();
        auto b2 = reader.readObject<StructB>();

        EXPECT_FLOAT_EQ(b2.real, 3.14159265359);
        EXPECT_EQ(b2.number, 1337);
    }

    std::filesystem::remove(tempFile);
}