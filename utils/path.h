#pragma once

#include "string.h"
#include <vector>

namespace Utils
{
    template <class T>
    class BasicPath : public BasicString<T>
    {
    public:
        BasicPath();

        BasicPath(const BasicPath<T> &cpy);

        BasicPath(const String &str);

        BasicPath(const T *str);

        BasicPath<T> &operator/(const BasicString<T> &rhs);

        bool exists() const;

        BasicPath<T> getCorrectCase() const;

        std::vector<BasicPath<T>> getFiles() const;

        std::vector<BasicPath<T>> getDirectories() const;

        BasicString<T> getDirectory() const;

        BasicString<T> getFilenameWithExt() const;

        BasicString<T> getFilename() const;

        BasicString<T> getExtension() const;

        static BasicPath<T> getTempDir();

        static BasicPath<T> getHomeDir();

        static BasicPath<T> getUserConfigDir();

        static BasicPath<T> getAppConfigDir();

    private:
        static const BasicString<T> DELIM;          //!< Path delimitor
        static const BasicString<T> PATH_UP;         //!< Path UP
        static const BasicString<T> FILE_EXT_DELIM; //!< Delimiter of the file extension
    }; //class BasicPath

    using Path = BasicPath<char>;
    using WPath = BasicPath<wchar_t>;
    //TODO: Implement BasicString<T> toUtf16 and toUtf32 and corresponsing fromAscii methods
    //      to instanciate unicode variants U16Path and U32Path, if needed.

} //namespace Utils
