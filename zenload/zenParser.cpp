#include "zenParser.h"
#include <fstream>
#include "parserImplASCII.h"
#include "parserImplBinSafe.h"
#include "parserImplBinary.h"
#include <algorithm>
#include <cctype>
#include "utils/logger.h"
#include "oCWorld.h"
#include "zCMesh.h"
#include "zCBspTree.h"
#include <vdfs/fileIndex.h>

using namespace ZenLoad;
using namespace Utils;

#ifdef __ANDROID__
#define ERROR(msg) do{LogError() << msg;}while(0)
#else 
#define ERROR(msg) do{ throw std::runtime_error(msg); }while(0)
#endif

ZenParser::ZenParser(const String &file)
    : m_Seek(0)
    , m_pWorldMesh(0)
{
    // Get data from zenfile
    readFile(file, m_Data);
}

ZenParser::ZenParser(const String &file, const VDFS::FileIndex &vdfs)
    : m_Seek(0)
    , m_pWorldMesh(0)
{
    vdfs.getFileData(file, m_Data);
}

ZenParser::ZenParser(const uint8_t *data, size_t size)
    : m_Seek(0)
    , m_pWorldMesh(0)
{
    m_Data.assign(data, data + size);
}

ZenLoad::ZenParser::~ZenParser()
{
    delete m_pWorldMesh;
}

bool ZenParser::readFile(const String &fileName, std::vector<uint8_t> &data)
{
    std::ifstream file(fileName, std::ios::in | std::ios::ate | std::ios::binary);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    if(!file.good())
    {
        ERROR("File does not exist");
        ERROR(strerror(errno));
    }
    LogInfo() << "Zen-File found! Size: " << size;

    data.resize(size);

    LogInfo() << "Reading...";
    file.read(reinterpret_cast<char *>(data.data()), size);

    return true;
}

void ZenParser::readHeader()
{
    readHeader(m_Header, m_pParserImpl);
}

void ZenParser::skipHeader()
{
    ZenHeader header;
    ParserImpl* impl = nullptr;
    readHeader(header, impl);

    delete impl;
}

void ZenParser::readHeader(ZenHeader &header, ParserImpl *&impl)
{
    if(!skipString("ZenGin Archive"))
        ERROR("Not a valid format");

    if(!skipString("ver"))
        ERROR("Not a valid header");

    // Version should be always 1...
    header.version = readIntASCII();

    // Skip archiver type
    skipString();

    // Read file-type, to create the right archiver implementation
    String fileType = readLine();
    if(fileType == "ASCII")
    {
        header.fileType = FT_ASCII;
        impl = new ParserImplASCII(this);
    }
    else if(fileType == "BINARY")
    {
        header.fileType = FT_BINARY;
        impl = new ParserImplBinary(this);
    }
    else if(fileType == "BIN_SAFE")
    {
        header.fileType = FT_BINSAFE;
        impl = new ParserImplBinSafe(this);
    }
    else
        ERROR("Unsupported file format");

    // Read string of the format "savegame b", where b is 0 or 1
    if(!skipString("saveGame"))
        ERROR("Unsupported file format");

    header.saveGame = readBoolASCII();

    // Read possible date
    if(skipString("date"))
    {
        header.date = readString() + " ";
        header.date += readString();
    }

    // Skip possible user
    if(skipString("user"))
        header.user = readLine();

    // Reached the end of the main header
    if(!skipString("END"))
        ERROR("No END in header(1)");

    // Continue with the implementationspecific header
    skipSpaces();

    impl->readImplHeader();
}

void ZenParser::readWorld(oCWorldData &info)
{
    LogInfo() << "ZEN: Reading world...";

    ChunkHeader header;
    readChunkStart(header);

    if(header.classname != "oCWorld:zCWorld")
        ERROR("Expected oCWorld:zCWorld-Chunk not found!");

    oCWorld::readObjectData(info, *this, header.version);
}

void ZenParser::readWorldMesh(oCWorldData &info)
{
    LogInfo() << "ZEN: Reading mesh...";
    m_pWorldMesh = new zCMesh;

    // Read worldmesh, if needed
    if(m_pWorldMesh)
    {
        /*size_t totalStart = m_Seek;
        readBinaryDWord();
        size_t size = readBinaryDWord();
        size_t start = m_Seek;
        m_pWorldMesh->readObjectData(*this);

        m_Seek = start + size;

        m_Seek = totalStart;*/
        info.bspTree = zCBspTree::readObjectData(*this, m_pWorldMesh);

        //m_pWorldMesh->readObjectData(*this);
    }
    else
    {
        // Skip
        readBinaryDWord(); // Version
        m_Seek += readBinaryDWord();
    }

    LogInfo() << "ZEN: Done reading mesh!";
}

void ZenParser::readChunkTest()
{
    /*ChunkHeader header;
    m_pParserImpl->readChunkStart(header);

    if(header.name == "MeshAndBsp")
    {
        readWorldMesh();
        return;
    }

    if(header.classname != "oCWorld:zCWorld")
        return;

    String str;
    do
    {
        size_t ts = m_Seek;
        ParserImpl::EZenValueType type;
        size_t size;


        m_pParserImpl->readEntryType(type, size);

        if(type != ParserImpl::ZVT_STRING)
        {
            m_Seek = ts;
            std::vector<uint8_t> data(size);
            m_pParserImpl->readEntry("", data.data(), size, ParserImpl::ZVT_0);
        }

        if(type == ParserImpl::ZVT_STRING)
        {
            m_Seek = ts;
            String str; str.resize(size);
            m_pParserImpl->readEntry("", &str, size, ParserImpl::ZVT_STRING);

            if(str.front() == '[' && str.size() > 2)
            {
                m_Seek = ts;
                readChunkTest();
                return;
            }
        }
    }while(str != "[]");*/
}

bool ZenParser::readChunkStart(ChunkHeader &header)
{
    return m_pParserImpl->readChunkStart(header);
}

bool ZenParser::readChunkEnd()
{
    return m_pParserImpl->readChunkEnd();
}

void ZenParser::skipChunk()
{
    size_t level = 1;

    do
    {
        ChunkHeader header;
        if(readChunkStart(header))
        {
            level++;
        }
        else if(readChunkEnd())
        {
            level--;
        }
        else
        {
            skipEntry();
        }

    }while(level > 0);
}

void ZenParser::skipEntry()
{
    ParserImpl::EZenValueType type;
    size_t size;
    size_t ts = m_Seek;

    // Read type and size first, so we can allocate the data
    m_pParserImpl->readEntryType(type, size);

    // Skip the entry
    m_Seek += size;
}

int32_t ZenParser::readIntASCII()
{
    skipSpaces();
    String number;
    while(m_Data[m_Seek] >= '0' && m_Data[m_Seek] <= '9')
    {
        number += m_Data[m_Seek];
        ++m_Seek;
    }
    return std::stoi(number);
}

bool ZenParser::readBoolASCII()
{
    skipSpaces();
    bool retVal;
    if(m_Data[m_Seek] != '0' && m_Data[m_Seek] != '1')
        ERROR("Value is not a bool");
    else
        retVal = m_Data[m_Seek] == '0' ? false : true;

    ++m_Seek;
    return retVal;
}

String ZenParser::readString(bool skip)
{
    if(skip)
        skipSpaces();

    String str;
    while(m_Data[m_Seek] != '\r' && m_Data[m_Seek] != '\n' && m_Data[m_Seek] != ' ')
    {
        str += m_Data[m_Seek];
        ++m_Seek;
    }
    return str;
}

bool ZenParser::skipString(const String &pattern)
{
    skipSpaces();
    bool retVal = true;
    if(pattern.empty())
    {
        while(!(m_Data[m_Seek] == '\n' || m_Data[m_Seek] == ' '))
            ++m_Seek;
        ++m_Seek;
    }
    else
    {
        size_t lineSeek = 0;
        while(lineSeek < pattern.size())
        {
            if(m_Data[m_Seek] != pattern[lineSeek])
            {
                retVal = false;
                break;
            }

            ++m_Seek;
            ++lineSeek;
        }
    }

    return retVal;
}

void ZenParser::skipSpaces()
{
    bool search = true;
    while(search && m_Seek < m_Data.size())
    {
        switch(m_Data[m_Seek])
        {
            case ' ':
            case '\r':
            case '\t':
            case '\n':
                ++m_Seek;
                break;
            default:
                search = false;
                break;
        }
    }
}

void ZenParser::skipNewLines()
{
    while(m_Seek < m_Data.size() && m_Data[m_Seek] == '\n')
        ++m_Seek;
}

void ZenParser::checkArraySize()
{
    if(m_Seek >= m_Data.size())
        throw std::logic_error("Out of range");
}

uint32_t ZenParser::readBinaryDWord()
{
    uint32_t retVal;
    readStructure(retVal);

    return retVal;
}

uint16_t ZenParser::readBinaryWord()
{
    uint16_t retVal;
    readStructure(retVal);

    return retVal;
}

uint8_t ZenParser::readBinaryByte()
{
    uint8_t retVal = *reinterpret_cast<uint8_t *>(&m_Data[m_Seek]);
    m_Seek += sizeof(uint8_t);
    return retVal;
}

float ZenParser::readBinaryFloat()
{
    float retVal;
    readStructure(retVal);

    return retVal;
}

void ZenParser::readBinaryRaw(void* target, size_t numBytes)
{
    if (target != nullptr && numBytes != 0)
    {
        std::memcpy(target, &m_Data[m_Seek], numBytes);
        m_Seek += numBytes;
    }
}

String ZenParser::readLine(bool skip)
{
    String retVal;
    while(m_Data[m_Seek] != '\r' && m_Data[m_Seek] != '\n' && m_Data[m_Seek] != '\0')
    {
        checkArraySize();
        retVal += m_Data[m_Seek++];
    }

    // Skip trailing \n\r\0
    //if(m_Header.fileType == FT_BINARY)
    m_Seek++;

    if(skip)
        skipSpaces();
    return retVal;
}
