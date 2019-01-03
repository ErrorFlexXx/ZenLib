#include "path.h"

#include <physfs.h>
#include "../lib/physfs/extras/ignorecase.h"

using namespace std;
using namespace Utils;

template <class T>
const BasicString<T> BasicPath<T>::DELIM = BasicString<T>::fromAsci("/");

template <class T>
const BasicString<T> BasicPath<T>::PATH_UP = BasicString<T>::fromAsci("..");

template <class T>
const BasicString<T> BasicPath<T>::FILE_EXT_DELIM = BasicString<T>::fromAsci(".");

template <class T>
BasicPath<T>::BasicPath()
    : BasicString<T>()
{}

template <class T>
BasicPath<T>::BasicPath(const String &str)
    : BasicString<T>(BasicString<T>().fromAsci(str.c_str()))
{}

template <class T>
BasicPath<T>::BasicPath(const T *str)
    : BasicString<T>(str)
{}

template <class T>
BasicPath<T>::BasicPath(const BasicPath<T> &cpy)
    : BasicString<T>(cpy)
{}

template <class T>
bool BasicPath<T>::exists() const
{
    PHYSFS_Stat stat;
    return 0 != PHYSFS_stat(this->toString().c_str(), &stat);
}

template <class T>
BasicPath<T> BasicPath<T>::getCorrectCase() const
{
    Path corr = this->toString();
    PHYSFSEXT_locateCorrectCase(&corr.at(0));
    return corr;
}

template <class T>
vector<BasicPath<T>> BasicPath<T>::getFiles() const
{
        vector<BasicPath<T>> vec;
        if (!exists())
            return vec;

        char **files = PHYSFS_enumerateFiles(this->toString().c_str());
        char **i;
        for (i = files; *i != nullptr; i++)
        {
            String entry;
            vec.push_back(entry.fromAsci(*i));
        }
        PHYSFS_freeList(files);
        return vec;
}

template <class T>
BasicString<T> BasicPath<T>::getDirectory() const
{
    return this->substr(0, this->find_last_of(DELIM));
}

template <class T>
BasicString<T> BasicPath<T>::getFilenameWithExt() const
{
    BasicString<T> filename;
    auto dirParts = this->split(DELIM);
    return dirParts.back();
}

template <class T>
BasicString<T> BasicPath<T>::getFilename() const
{
    BasicString<T> filename;
    auto filenameParts = getFilenameWithExt().split(FILE_EXT_DELIM);

    for(size_t i = 0; i < filenameParts.size() - 1; i++) //Copy filename, wo. ext.
    {
        filename += filenameParts[i];
    }
    return filename;
}

template <class T>
BasicString<T> BasicPath<T>::getExtension() const
{
    return getFilenameWithExt().split(FILE_EXT_DELIM).back();
}

//Please compile template class for the following types:
template class BasicPath<char>;
template class BasicPath<wchar_t>;
