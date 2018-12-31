#pragma once

#include <string>
#include <sstream>
#include <vector>

namespace Utils
{   
    /**
     * @brief Class BasicString extendable string class for different char types.
     */
    template <class T>
    class BasicString : public std::basic_string<T, std::char_traits<T>, std::allocator<T>>
    {
    public:
        BasicString();

        /**
         * @brief BasicString constructs a BasicString object from an const ptr initializer.
         * @param (in) s string to initialize this String objects with.
         */
        BasicString(const T *s);

        BasicString(const BasicString<T> &s);

        BasicString(const std::basic_string<T> &s);

        BasicString &toUpper();

        BasicString &toLower();

        std::vector<BasicString<T>> split(const T delim, std::vector<BasicString<T>> &elems);

        std::vector<BasicString<T>> split(const T delim);

        std::vector<BasicString<T>> split(const BasicString<T> &delim) const;
    }; //class BasicString

    using String    = BasicString<char>;
    using WString   = BasicString<wchar_t>;
    using U16String = BasicString<char16_t>;
    using U32String = BasicString<char32_t>;

    template <class T>
    class BasicStringStream : public std::basic_stringstream<T, std::char_traits<T>, std::allocator<T>>
    {
    public:
        BasicStringStream();
        BasicStringStream(BasicString<T> &str);
    }; //class BasicStringStream

    using StringStream = BasicStringStream<char>;
    using WStringStream = BasicStringStream<wchar_t>;
    using U16StringStream = BasicStringStream<char16_t>;
    using U32StringStream = BasicStringStream<char32_t>;

} //namespace Utils
