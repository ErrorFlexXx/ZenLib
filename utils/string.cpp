#include "string.h"
#include "logger.h"
#include <algorithm>
#include <locale>  //Converting ...
#include <codecvt> //Converting ascii, utf16, utf32

using namespace std;
using namespace Utils;

template <class T>
BasicString<T>::BasicString()
    : basic_string<T>()
{}

template <class T>
BasicString<T>::BasicString(const T *s)
    : basic_string<T>(s)
{}

template <class T>
BasicString<T>::BasicString(const T *s, size_t n)
    : basic_string<T>(s, n)
{}

template <class T>
BasicString<T>::BasicString(const BasicString<T> &s)
    : basic_string<T>(s)
{}

template <class T>
BasicString<T>::BasicString(const std::basic_string<T> &s)
    : basic_string<T>(s)
{}

template <class T>
BasicString<T> BasicString<T>::toLower() const
{
    BasicString<T> tmp = *this;
    transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
    return tmp;
}

template <class T>
BasicString<T> BasicString<T>::toUpper() const
{
    BasicString<T> tmp = *this;
    transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);
    return tmp;
}

template <>
BasicString<char> BasicString<char>::toString() const
{
    return *this; //Copy
}

template <>
BasicString<char> BasicString<wchar_t>::toString() const
{
    setlocale(LC_CTYPE, "");
    return std::string(this->begin(), this->end()).c_str();
}

template <>
BasicString<char> BasicString<char16_t>::toString() const
{
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
    return BasicString<char>(convert.to_bytes(this->c_str()));
}

template <>
BasicString<char> BasicString<char32_t>::toString() const
{
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
    return BasicString<char>(convert.to_bytes(this->c_str()));
}

template <>
BasicString<wchar_t> BasicString<char>::toWString() const
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return std::wstring(converter.from_bytes(this->c_str()));
}

template <>
BasicString<wchar_t> BasicString<wchar_t>::toWString() const
{
    return *this;
}

template <>
BasicString<wchar_t> BasicString<char16_t>::toWString() const
{
    wstring_convert<codecvt_utf16<wchar_t, 0x10ffff, little_endian>, wchar_t> conv;
    wstring ws = conv.from_bytes(
                         reinterpret_cast<const char*> (&this->at(0)),
                         reinterpret_cast<const char*> (&this->at(0) + this->size()));
    return ws;
}

template <>
BasicString<wchar_t> BasicString<char32_t>::toWString() const
{
    return this->toString().toWString(); //FIXME: Find a direct way of converting this.
}

template <>
BasicString<char> BasicString<char>::fromAsci(const char* str)
{
    return String(str);
}

template <>
BasicString<wchar_t> BasicString<wchar_t>::fromAsci(const char* str)
{
    BasicString<char> conv = str;
    return conv.toWString();
}

//Functions injected to std:
namespace std
{
    /**
     * @brief stoi string to int conversion function for BasicString Utf16.
     */
    int stoi(const BasicString<char16_t> &str, size_t *&pos, int &base)
    {
        return stoi(str.toString().c_str(), pos, base);
    }

    /**
     * @brief stoi string to int conversion function for BasicString Utf32.
     */
    int stoi(const BasicString<char32_t> &str, size_t *&pos, int &base)
    {
        return stoi(str.toString().c_str(), pos, base);
    }

    /**
     * @brief stol string to long conversion function for BasicString Utf16.
     */
    long stol(const BasicString<char16_t> &str, size_t *&pos, int &base)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
        return stol(convert.to_bytes(str.c_str()), pos, base);
    }

    /**
     * @brief stol string to long conversion function for BasicString Utf32.
     */
    long stol(const BasicString<char32_t> &str, size_t *&pos, int &base)
    {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
        return stol(convert.to_bytes(str.c_str()), pos, base);
    }
}

template <class T>
int BasicString<T>::toInt(size_t *pos, int base) const
{
    return std::stoi(*this, pos, base);
}

template <class T>
long BasicString<T>::toLong(size_t *pos, int base) const
{
    return std::stol(*this, pos, base);
}

template <class T>
bool BasicString<T>::isNumber() const
{
    return !this->empty() && std::find_if(this->begin(), this->end(), [](unsigned char c){return !std::isdigit(c); }) == this->end();
}

template <class T>
bool BasicString<T>::equals(const BasicString<T> &rhs) const
{
    if(this->length() == rhs.length())
    {
        return this->find(rhs) == 0;
    }
    return false;
}

template <class T>
bool BasicString<T>::operator==(const BasicString<T> &rhs) const
{
    return this->equals(rhs);
}

template <class T>
bool BasicString<T>::operator==(const T *rhs) const
{
    return this->equals(BasicString<T>(rhs));
}

template <class T>
bool BasicString<T>::contains(const BasicString<T> &search, bool ignoreCase) const
{
    if(ignoreCase)
    {
        BasicString<T> str       = this->toUpper();
        BasicString<T> searchStr = search.toUpper();

        return (str.find(searchStr) != BasicString::npos);
    }
    return (this->find(search) != BasicString::npos);
}

template <class T>
BasicString<T> &BasicString<T>::replace(const BasicString<T> &search, const BasicString<T> &replace)
{
    size_t pos = 0;
    while ((pos = this->find(search, pos)) != std::string::npos) //While search is found..
    {
        this->std::basic_string<T>::replace(pos, search.length(), replace); //Replace it
        pos += replace.length();
    }
    return *this;
}

template <class T>
std::vector<BasicString<T>> &BasicString<T>::split(const T delim, std::vector<BasicString<T>> &elems) const
{
    BasicStringStream<T> ss(*this);
    BasicString<T> item;
    while (std::getline(ss, item, delim))
        elems.push_back(item);

    return elems;
}

template <class T>
std::vector<BasicString<T>> BasicString<T>::split(const T delim) const
{
    std::vector<BasicString> vec;
    return split(delim, vec);
}

template <class T>
std::vector<BasicString<T>> BasicString<T>::split(const BasicString<T> &delim) const
{
    std::vector<BasicString<T>> parts;
    BasicString<T> tmp = *this;
    size_t index = tmp.find(delim);

    while(index != BasicString<T>::npos)
    {
        if(index != 0)
            parts.push_back(tmp.substr(0, index));      //Take part up to delim
        tmp = tmp.substr(index + delim.length());   //Cut off part + delim
        index = tmp.find(delim);
    }

    if(!tmp.empty())
        parts.push_back(tmp);

    return parts;
}

template <class T>
BasicStringStream<T>::BasicStringStream()
    : std::basic_stringstream<T>()
{}

template <class T>
BasicStringStream<T>::BasicStringStream(const BasicString<T> &str)
    : std::basic_stringstream<T>(str)
{}

//Please compile template class for the following types:
template class BasicString<char>;
template class BasicString<wchar_t>;
template class BasicString<char16_t>;
template class BasicString<char32_t>;

template class BasicStringStream<char>;
template class BasicStringStream<wchar_t>;
template class BasicStringStream<char16_t>;
template class BasicStringStream<char32_t>;
