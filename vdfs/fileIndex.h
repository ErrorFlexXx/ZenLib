#pragma once

#include <utils/string.h>
#include <unordered_map>
#include <vector>
#include <set>
#include <map>

namespace VDFS
{
    class FileIndex
    {
    public:
        FileIndex();
        ~FileIndex();

        /**
         * @brief Initializes the VDFS
         */
        static void initVDFS(const char *argv0);

        /**
         * @brief Loads a VDF-File and initializes everything
         */
        bool loadVDF(const Utils::String &vdf, uint32_t priority = 0, const Utils::String &mountPoint = "/");

        /**
         * Mounts the given folder-structure into the file-index
         * @param path folder to mount
         * @return success
         */
        bool mountFolder(const Utils::String &path, const Utils::String &mountPoint = "/");

        /**
         * Must be called after you have mounted/loaded all files. Otherwise files won't be openable.
         */
        void finalizeLoad();

        /**
         * @brief Fills a vector with the data of the given file
         */
        bool getFileData(const Utils::String &file, std::vector<uint8_t> &data) const;

        /**
         * @brief Returnst the list of all known files
         */
        std::vector<Utils::String> getKnownFiles(const Utils::String &path = "/") const;

        /**
         * @return Whether a file with the given name exists
         */
        bool hasFile(const Utils::String &name) const;

        /**
         * Get the last modification time of the given VDF-File.
         * @param name of the VDF-File
         * @return If successful then the datetime inside the VDF header which represents
         * the last modification time of the VDF-File will be returned as seconds since
         * the unix epoch 00:00, Jan 1 1970 UTC otherwise -1.
         */
        static int64_t getLastModTime(const Utils::String &name);

    private:
        /**
         * @return Whether this fileindex has been finalized
         */
        bool isFinalized() const;

        /**
         * Updates the cache used by findCaseSensitiveNameOf
         */
        void updateUpperedFilenamesMap();

        /**
         * @return Case-sensitive version of the given case-insensitive filename. Empty string if not found.
         */
        Utils::String findCaseSensitiveNameOf(const Utils::String &caseInsensitiveName) const;

        std::map<Utils::String, Utils::String> m_FilenamesByUpperedFileNames;
    };
}
