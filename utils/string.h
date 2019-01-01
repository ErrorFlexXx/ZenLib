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

        /**
         * @brief BasicString constructs a BasicString object from an const ptr initializer.
         * @param s ptr to character to init from.
         * @param n elements are taken from s
         */
        BasicString(const T *s, size_t n);

        /**
         * @brief BasicString Copy constructor.
         * @param s to copy.
         */
        BasicString(const BasicString<T> &s);

        /** @copydoc BasicString<T>::BasicString(const BasicString<T> &s) */
        BasicString(const std::basic_string<T> &s);

        /**
         * @brief toUpper uppers a string.
         * @return an upper case representation of this string.
         */
        BasicString toUpper() const;

        /**
         * @brief toLower lowers a string.
         * @return  a lower case representation of this string.
         */
        BasicString toLower() const;

        /**
         * @brief toInt casts this string to an integer.
         * @param pos position index to start interpreting at.
         * @param base for the conversion.
         * @return the resulting integer.
         */
        int toInt(size_t *pos = nullptr, int base = 10) const;

        /**
         * @brief isNumber checks, if the current string is a valid number.
         * @return true if contained chars are numerics, false otherwise.
         */
        bool isNumber() const;

        /**
         * @brief equals checks, if the right hand side string has an identical content.
         * @param rhs string to compare with.
         * @return true, if identical contents, false otherwise.
         */
        bool equals(const BasicString<T> &rhs) const;

        /** @copydoc BasicString<T>::equals */
        bool operator==(const BasicString<T> &rhs) const;

        /** @copydoc BasicString<T>::equals */
        bool operator==(const T *rhs) const;

        /**
         * @brief contains checks, if a string is contained in this string.
         * @param search the content to search for in this string.
         * @param ignoreCase flag specifying, if the case shall be ignored.
         * @return true, if the search string is contained in this string.
         */
        bool contains(const BasicString<T> &search, bool ignoreCase = true) const;

        /**
         * @brief replace replace all occurences of search with replace.
         * @param search to replace
         * @param replace to replace with
         * @return a reference to this string.
         */
        BasicString<T> &replace(const BasicString<T> &search, const BasicString<T> &replace);

        /**
         * @brief split splits a and stores the elements in the given vector.
         * @param delim character delimeter to split at.
         * @param elems out elements found.
         * @return reference of the given vector.
         */
        std::vector<BasicString<T>> &split(const T delim, std::vector<BasicString<T>> &elems) const;

        /**
         * @brief split splits a string with a given char delimiter.
         * @param delim to split at.
         * @return a vector containing the resulting parts.
         */
        std::vector<BasicString<T>> split(const T delim) const;

        /**
         * @brief split splits a string with a given delimiter string.
         * @param delim string to split with.
         * @return a vector containing the resulting parts.
         */
        std::vector<BasicString<T>> split(const BasicString<T> &delim) const;
    }; //class BasicString

    //Using directives for common string types:
    using String    = BasicString<char>;        //8-Bit ASCII String
    using WString   = BasicString<wchar_t>;     //8-Bit Wide char String
    using U16String = BasicString<char16_t>;    //16-Bit Unicode String.
    using U32String = BasicString<char32_t>;    //32-Bit Unicode String.

    template <class T>
    class BasicStringStream : public std::basic_stringstream<T, std::char_traits<T>, std::allocator<T>>
    {
    public:
        BasicStringStream();
        BasicStringStream(const BasicString<T> &str);
    }; //class BasicStringStream

    using StringStream = BasicStringStream<char>;
    using WStringStream = BasicStringStream<wchar_t>;
    using U16StringStream = BasicStringStream<char16_t>;
    using U32StringStream = BasicStringStream<char32_t>;

} //namespace Utils

namespace std
{
    template <class T>
    /**
     * @brief The hash<Utils::BasicString<T> > struct
     *        Injection of a hash function required to use this BasicStrings in containers like
     *        unordered maps or pairs.
     */
    struct hash<Utils::BasicString<T>>
    {
        size_t operator()(const Utils::BasicString<T> &s) const
        {
            std::hash<std::basic_string<T>> hash_fn;
            return hash_fn(s);
        }
    };
}
