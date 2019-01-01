#pragma once

#include "zTypes.h"
#include <utils/string.h>
#include <map>

namespace VDFS
{
    class FileIndex;
}

namespace ZenLoad
{
    class ZenParser;

    class zCCSLib
    {
    public:
        /**
         * @brief Loads the file from the given VDF-Archive
         */
        zCCSLib(const Utils::String &fileName, const VDFS::FileIndex &fileIndex);
        zCCSLib(const Utils::String &file);

        /**
         * Reads this object from an internal zen
         */
        void readObjectData(ZenParser &parser);

        /**
         * @return the message of the given name
         */
        const oCMsgConversationData &getMessageByName(const Utils::String &name);

        /**
         * @return true if the message was found
         */
        bool messageExists(const Utils::String &name) const;

        const zCCSLibData &getData(){ return m_Data; }

    private:
        /**
         * Loaded data straight from the file
         */
        zCCSLibData m_Data;

        /**
         * Message indices by their names
         */
        std::map<Utils::String, size_t> m_MessagesByName;
    }; //class zCCSLib
} //namespace ZenLoad
