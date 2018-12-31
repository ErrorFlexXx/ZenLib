#include <utils/string.h>
#include <gtest/gtest.h>
#include <utils/logger.h>

using namespace Utils;

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(STRING, splitChar)
{
    String test = "1,2,3,4,5,6,7,8,9,10";
    auto parts = test.split(',');
    ASSERT_EQ(parts.size(), 10);
    ASSERT_EQ(parts.at(5).at(0), '6');
}

TEST(WSTRING, splitWChar)
{
    WString test = L"1,2,3,4,5,6,7,8,9,10";
    auto parts = test.split(L',');
    ASSERT_EQ(parts.size(), 10);
    ASSERT_EQ(parts.at(5).at(0), L'6');
}

TEST(U16STRING, splitU16Char)
{
    U16String test = u"1,2,3,4,5,6,7,8,9,10";
    auto parts = test.split(u',');
    ASSERT_EQ(parts.size(), 10);
    ASSERT_EQ(parts.at(5).at(0), u'6');
}

TEST(U32STRING, splitU32Char)
{
    U32String test = U"1,2,3,4,5,6,7,8,9,10";
    auto parts = test.split(U',');
    ASSERT_TRUE(parts.size() == 10);
    ASSERT_EQ(parts.at(5).at(0), U'6');
}

TEST(STRING, splitString)
{
    String test = "1,2,3,4,5,6,7,8,9,10";
    auto parts = test.split(",");
    ASSERT_EQ(parts.size(), 10);
    ASSERT_EQ(parts.at(5).at(0), '6');
}

TEST(WSTRING, splitWString)
{
    WString test = L"1,2,3,4,5,6,7,8,9,10";
    auto parts = test.split(L",");
    ASSERT_EQ(parts.size(), 10);
    ASSERT_EQ(parts.at(5).at(0), L'6');
}

TEST(U16STRING, splitU16String)
{
    U16String test = u"1,2,3,4,5,6,7,8,9,10";
    auto parts = test.split(u",");
    //Fixme: split with string delim failing for u16 and u32 (throwing bad_cast).
    //Reason: Shall be Traits for char16_t and char32_t are missing in current std lib.
    //        Misterious that std::getline with char16_t is working, but with char16_t string not.
    ASSERT_EQ(parts.size(), 10);
    ASSERT_EQ(parts.at(5).at(0), u'6');
}

TEST(U32STRING, splitU32String)
{
    U32String test = U"1,2,3,4,5,6,7,8,9,10";
    auto parts = test.split(U",");
    //Fixme: split with string delim failing for u16 and u32 (throwing bad_cast).
    //Reason: Shall be Traits for char16_t and char32_t are missing in current std lib.
    //        Misterious that std::getline with char16_t is working, but with char16_t string not.
    ASSERT_TRUE(parts.size() == 10);
    ASSERT_EQ(parts.at(5).at(0), U'6');
}

