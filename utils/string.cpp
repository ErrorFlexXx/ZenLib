#include "string.h"
#include "logger.h"
#include <algorithm>

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
BasicString<T>::BasicString(const BasicString<T> &s)
    : basic_string<T>(s)
{}

template <class T>
BasicString<T>::BasicString(const std::basic_string<T> &s)
    : basic_string<T>(s)
{}

template <class T>
BasicString<T> &BasicString<T>::toLower()
{
    transform(this->begin(), this->end(), this->begin(), ::tolower);
    return *this;
}

template <class T>
BasicString<T> &BasicString<T>::toUpper()
{
    transform(this->begin(), this->end(), this->begin(), ::toupper);
    return *this;
}

template <class T>
std::vector<BasicString<T>> BasicString<T>::split(const T delim, std::vector<BasicString<T>> &elems)
{
    BasicStringStream<T> ss(*this);
    BasicString<T> item;
    while (std::getline(ss, item, delim))
        elems.push_back(item);

    return elems;
}

template <class T>
std::vector<BasicString<T>> BasicString<T>::split(const T delim)
{
    std::vector<BasicString> vec;
    return split(delim, vec);
}

template <class T>
std::vector<BasicString<T>> BasicString<T>::split(const BasicString<T> &delim) const
{
    std::vector<BasicString<T>> parts;
    BasicString<T> _s = *this;
    BasicStringStream<T> stringStream(_s);
    BasicString<T> line;
    while(std::getline(stringStream, line))
    {
        std::size_t prev = 0, pos;
        while ((pos = line.find_first_of(delim, prev)) != BasicString::npos)
        {
            if (pos > prev)
                parts.push_back(line.substr(prev, pos-prev));
            prev = pos + 1;
        }
        if (prev < line.length())
            parts.push_back(line.substr(prev, BasicString::npos));
    }

    return parts;
}

template <class T>
BasicStringStream<T>::BasicStringStream()
    : std::basic_stringstream<T>()
{}

template <class T>
BasicStringStream<T>::BasicStringStream(BasicString<T> &str)
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

