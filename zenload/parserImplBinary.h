#pragma once

#include "parserImpl.h"

namespace ZenLoad
{
    class ParserImplBinary : public ParserImpl
    {
        friend ZenParser;
    public:
        ParserImplBinary(ZenParser *parser);

        /** @copydoc ParserImpl::readImplHeader */
        virtual void readImplHeader();

        /** @copydoc ParserImpl::readChunkStart */
        virtual bool readChunkStart(ZenParser::ChunkHeader &header);

        /** @copydoc ParserImpl::readChunkEnd */
        virtual bool readChunkEnd();

        /** @copydoc ParserImpl::readString */
        virtual Utils::String readString();

        /** @copydoc ParserImpl::readEntry */
        virtual void readEntry(const Utils::String &name, void *target, size_t targetSize, EZenValueType expectedType = ZVT_0);

        /** @copydoc ParserImpl::readEntryType */
        virtual void readEntryType(EZenValueType &type, size_t &size);
    }; //class
} //namespace ZenLoad
