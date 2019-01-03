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
    String test = "1,2,3,4,5,6,7,8,9,0";
    auto parts = test.split(',');
    ASSERT_EQ(parts.size(), 10);
    ASSERT_EQ(parts.at(0).at(0), '1');
    ASSERT_EQ(parts.at(5).at(0), '6');
    ASSERT_EQ(parts.at(9).at(0), '0');
}

TEST(WSTRING, splitWChar)
{
    WString test = L"1,2,3,4,5,6,7,8,9,0";
    auto parts = test.split(L',');
    ASSERT_EQ(parts.size(), 10);
    ASSERT_EQ(parts.at(0).at(0), L'1');
    ASSERT_EQ(parts.at(5).at(0), L'6');
    ASSERT_EQ(parts.at(9).at(0), L'0');
}

TEST(U16STRING, splitU16Char)
{
    U16String test = u"1,2,3,4,5,6,7,8,9,0";
    auto parts = test.split(u',');
    ASSERT_EQ(parts.size(), 10);
    ASSERT_EQ(parts.at(0).at(0), u'1');
    ASSERT_EQ(parts.at(5).at(0), u'6');
    ASSERT_EQ(parts.at(9).at(0), u'0');
}

TEST(U32STRING, splitU32Char)
{
    U32String test = U"1,2,3,4,5,6,7,8,9,0";
    auto parts = test.split(U',');
    ASSERT_TRUE(parts.size() == 10);
    ASSERT_EQ(parts.at(0).at(0), U'1');
    ASSERT_EQ(parts.at(5).at(0), U'6');
    ASSERT_EQ(parts.at(9).at(0), U'0');
}

TEST(STRING, splitString)
{
    String test = "1,2,3,4,5,6,7,8,9,0";
    auto parts = test.split(",");
    ASSERT_EQ(parts.size(), 10);
    ASSERT_EQ(parts.at(0).at(0), '1');
    ASSERT_EQ(parts.at(5).at(0), '6');
    ASSERT_EQ(parts.at(9).at(0), '0');
}

TEST(WSTRING, splitWString)
{
    WString test = L"1,2,3,4,5,6,7,8,9,0";
    auto parts = test.split(L",");
    ASSERT_EQ(parts.size(), 10);
    ASSERT_EQ(parts.at(0).at(0), L'1');
    ASSERT_EQ(parts.at(5).at(0), L'6');
    ASSERT_EQ(parts.at(9).at(0), L'0');
}

TEST(U16STRING, splitU16String)
{
    U16String test = u"1,2,3,4,5,6,7,8,9,0";
    auto parts = test.split(u",");
    ASSERT_EQ(parts.size(), 10);
    ASSERT_EQ(parts.at(0).at(0), u'1');
    ASSERT_EQ(parts.at(5).at(0), u'6');
    ASSERT_EQ(parts.at(9).at(0), u'0');
}

TEST(U32STRING, splitU32String)
{
    U32String test = U"1,2,3,4,5,6,7,8,9,0";
    auto parts = test.split(U",");
    ASSERT_TRUE(parts.size() == 10);
    ASSERT_EQ(parts.at(0).at(0), U'1');
    ASSERT_EQ(parts.at(5).at(0), U'6');
    ASSERT_EQ(parts.at(9).at(0), U'0');
}

TEST(STRING, equalsString)
{
    String sample = "The quick brown fox jumps over the lazy dog.";
    String equalSample = "The quick brown fox jumps over the lazy dog.";
    String unequalSample = "The quick.";

    ASSERT_TRUE(sample.equals(equalSample));
    ASSERT_FALSE(sample.equals(unequalSample));
}

TEST(WSTRING, equalsWString)
{
    WString sample = L"The quick brown fox jumps over the lazy dog.";
    WString equalSample = L"The quick brown fox jumps over the lazy dog.";
    WString unequalSample = L"The quick.";

    ASSERT_TRUE(sample.equals(equalSample));
    ASSERT_FALSE(sample.equals(unequalSample));
}

TEST(U16STRING, equalsU16String)
{
    U16String sample = u"The quick brown fox jumps over the lazy dog.";
    U16String equalSample = u"The quick brown fox jumps over the lazy dog.";
    U16String unequalSample = u"The quick.";

    ASSERT_TRUE(sample.equals(equalSample));
    ASSERT_FALSE(sample.equals(unequalSample));
}

TEST(U32STRING, equalsU32String)
{
    U32String sample = U"The quick brown fox jumps over the lazy dog.";
    U32String equalSample = U"The quick brown fox jumps over the lazy dog.";
    U32String unequalSample = U"The quick.";

    ASSERT_TRUE(sample.equals(equalSample));
    ASSERT_FALSE(sample.equals(unequalSample));
}

TEST(STRING, toLowerString)
{
    String test = " !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    String lower = " !\"#$%&\'()*+,-./0123456789:;<=>?@abcdefghijklmnopqrstuvwxyz[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

    ASSERT_STREQ(test.toLower().c_str(), lower.c_str());
}

TEST(WSTRING, toLowerWString)
{
    WString test = L" !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    WString lower = L" !\"#$%&\'()*+,-./0123456789:;<=>?@abcdefghijklmnopqrstuvwxyz[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

    ASSERT_STREQ(test.toLower().c_str(), lower.c_str());
}

TEST(U16STRING, toLowerU16String)
{
    U16String test = u" !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    U16String lower = u" !\"#$%&\'()*+,-./0123456789:;<=>?@abcdefghijklmnopqrstuvwxyz[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

    ASSERT_TRUE(test.toLower().equals(lower));
}

TEST(U32STRING, toLowerU32String)
{
    U32String test = U" !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    U32String lower = U" !\"#$%&\'()*+,-./0123456789:;<=>?@abcdefghijklmnopqrstuvwxyz[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

    ASSERT_TRUE(test.toLower().equals(lower));
}

TEST(STRING, toUpperString)
{
    String test = " !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    String upper = " !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`ABCDEFGHIJKLMNOPQRSTUVWXYZ{|}~";

    ASSERT_STREQ(test.toUpper().c_str(), upper.c_str());
}

TEST(WSTRING, toUpperWString)
{
    WString test = L" !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    WString upper = L" !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`ABCDEFGHIJKLMNOPQRSTUVWXYZ{|}~";

    ASSERT_STREQ(test.toUpper().c_str(), upper.c_str());
}

TEST(U16STRING, toUpperU16String)
{
    U16String test = u" !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    U16String upper = u" !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`ABCDEFGHIJKLMNOPQRSTUVWXYZ{|}~";

    ASSERT_TRUE(test.toUpper().equals(upper));
}

TEST(U32STRING, toUpperU32String)
{
    U32String test = U" !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    U32String upper = U" !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`ABCDEFGHIJKLMNOPQRSTUVWXYZ{|}~";

    ASSERT_TRUE(test.toUpper().equals(upper));
}

TEST(STRING, replaceString)
{
    String test = "This is a test string, which is a good example.";
    String expectedResult = "This might be a test string, which might be a good example.";

    ASSERT_STREQ(test.replace(" is ", " might be ").c_str(), expectedResult.c_str());
}

TEST(WSTRING, replaceWString)
{
    WString test = L"This is a test string, which is a good example.";
    WString expectedResult = L"This might be a test string, which might be a good example.";

    ASSERT_STREQ(test.replace(L" is ", L" might be ").c_str(), expectedResult.c_str());
}

TEST(U16STRING, replaceU16String)
{
    U16String test = u"This is a test string, which is a good example.";
    U16String expectedResult = u"This might be a test string, which might be a good example.";

    ASSERT_TRUE(test.replace(u" is ", u" might be ").equals(expectedResult));
}

TEST(U32STRING, replaceU32String)
{
    U32String test = U"This is a test string, which is a good example.";
    U32String expectedResult = U"This might be a test string, which might be a good example.";

    ASSERT_TRUE(test.replace(U" is ", U" might be ").equals(expectedResult));
}

TEST(STRING, toString)
{
    String string = "This is a String.. /";
    WString wstring = L"This is a String.. /";
    U16String u16string = u"This is a String.. /";
    U32String u32string = U"This is a String.. /";

    ASSERT_STREQ(string.c_str(), wstring.toString().c_str());
    ASSERT_STREQ(string.c_str(), u16string.toString().c_str());
    ASSERT_STREQ(string.c_str(), u32string.toString().c_str());
}

TEST(WSTRING, toWString)
{
    String string = "This is a String.. /";
    WString wstring = L"This is a String.. /";
    U16String u16string = u"This is a String.. /";
    U32String u32string = U"This is a String.. /";

    ASSERT_STREQ(wstring.c_str(), string.toWString().c_str());
    ASSERT_STREQ(wstring.c_str(), u16string.toWString().c_str());
    ASSERT_STREQ(wstring.c_str(), u32string.toWString().c_str());
}
