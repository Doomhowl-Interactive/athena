#include <minerva/serialized_real.hh>
#include <gtest/gtest.h>

TEST(UtilsTests, TestSerializationPositive)
{
    auto data = minerva::serializeReal(3.14159265359);
    auto result = minerva::deserializeReal(data);

    EXPECT_FLOAT_EQ(result, 3.14159265359);
}

TEST(UtilsTest, TestSerializationNegative)
{
    auto data = minerva::serializeReal(-3.14159265359);
    auto result = minerva::deserializeReal(data);

    EXPECT_FLOAT_EQ(result, -3.14159265359);
}

TEST(UtilsTest, TestSerializationZero)
{
    auto data = minerva::serializeReal(0);
    auto result = minerva::deserializeReal(data);

    EXPECT_FLOAT_EQ(result, 0);
}
