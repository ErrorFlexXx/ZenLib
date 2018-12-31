#pragma once

#include <zenload/zCModelAni.h>

namespace ZenLoad
{
    class zCModelAni;
    class ZenParser;

    /**
     * @brief The ModelAnimationParser class a streaming parser for .MAN files.
     */
    class ModelAnimationParser
    {
    public:

        typedef std::vector<zCModelAniSample> Samples;
        typedef std::vector<uint32_t> NodeIndex;

        enum EChunkType
        {
            CHUNK_ERROR,
            CHUNK_EOF,

            CHUNK_HEADER    = 0xA020,
            CHUNK_RAWDATA   = 0xA090,
        };

        ModelAnimationParser(ZenParser &zen);

        void setScale(float scale) { m_Scale = scale; }

        /**
         * @brief getHeader returns the parsed header.
         *        Call this if parse() returns CHUNK_HEADER.
         * @return The header read during the last call to parse().
         */
        const zCModelAniHeader &getHeader() const { return m_Header; }

        /**
         * @brief getSamples returns the parsed samples.
         *        Call this if parse() returns CHUNK_RAWDATA.
         * @return The samples read during the last call to parse().
         */
        const Samples &getSamples() const { return m_Samples; }

        /**
         * @brief getNodeIndex returns the parsed nodes.
         *        Call this if parse() returns CHUNK_RAWDATA.
         * @return The nodes read during the last call to parse().
         */
        const NodeIndex &getNodeIndex() const { return m_NodeIndex; }

        EChunkType parse();

    private:
        ZenParser           &m_Zen;
        float               m_Scale = 1.0f;
        zCModelAniHeader    m_Header;
        Samples             m_Samples;
        NodeIndex           m_NodeIndex;

        void readHeader();
        void readRawData();
    }; //class ModelAnimationParser
} //namespace ZenLoad
