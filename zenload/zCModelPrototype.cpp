#include "zCModelPrototype.h"
#include "zenParser.h"
#include "utils/logger.h"
#include "zTypes.h"
#include <algorithm>
#include <stdlib.h>
#include "vdfs/fileIndex.h"
#include "utils/alignment.h"

using namespace ZenLoad;
using namespace Utils;

enum class EIdxAni : int
{
    def,
    name,
    layer,
    nextAni,
    blendIn,
    blendOut,
    flags,
    ASC_Name,
    aniDir,
    startFrame,
    endFrame,
    fps,
};

enum class EIdxMeshAndTree
{
    def,
    name,
    dontUseMesh
};

enum class EIdxRegisterMesh
{
    def,
    name
};

/**
 * Splits one of the MDS-Declerations like the example seen inside the function
 * @param _line line to parse
 * @return Vector of all parameters as strings
 */
std::vector<String> splitDecl(const String &_line)
{
    // Example: registerMesh ("Gob_Body.ASC")
    // Example: ani			("s_FistRun"					1	"s_FistRun"			0.1	0.1	M.	"Gob_1hRunAmbient_M01.asc"	F	0	30	FPS:10)

    // Collapse
    std::vector<String> out;
    out.push_back("");
    bool inArg = true;
    for(auto &c : _line)
    {
        if(c == ' ' || c == '\t' || c == '(')
        {
            if (inArg) // Only add a new section, when the last one was filled
            {
                out.push_back("");
                inArg = false;
            }
        }
        else
        {
            if (c != '"' && c != ')') // Don't add quotes and the closing bracket
            {
                out.back() += c;
                inArg = true;
            }

            // Handle empty strings
            if(c == '"')
                inArg = true;
        }
    }

    return out;
}

zCModelPrototype::zCModelPrototype(const String &fileName, const VDFS::FileIndex &fileIndex)
{
    std::vector<uint8_t> data;
    fileIndex.getFileData(fileName, data);

    if(data.empty())
        return; // TODO: Throw an exception or something

    try
    {
        // Create parser from memory
        // FIXME: There is an internal copy of the data here. Optimize!
        ZenLoad::ZenParser parser(data.data(), data.size());

        readObjectData(parser);
    }
    catch(std::exception &e)
    {
        LogError() << e.what();
        return;
    }
}

void zCModelPrototype::readObjectData(ZenParser &parser)
{
    // TODO: Implement G2-Variant of this

    enum Section
    {
        Model,
        AniEnum,
        MeshAndTree,
        RegisterMesh,
        StartMesh,
    };

    /**
     * Ani enum
     */
    auto readAniEnum = [&]()
    {
        while (parser.getSeek() < parser.getFileSize())
        {
            String line = parser.readLine(true);
            std::transform(line.begin(), line.end(), line.begin(), ::tolower);

            LogInfo() << "MDS-Line: " << line;

            if (line.find("//") != String::npos)
                continue; // Skip comments. These MUST be on their own lines, by definition.
            else if (line.find("}") != String::npos)
                break; // There can be only one } per block

        }
    };

    /**
     * Register mesh
     */
    auto readRegisterMesh = [&](const String &line) {
        std::vector<String> args = splitDecl(line);

        LogInfo() << "Args: " << args;
    };

    /**
     * Ani
     */
    auto readAni = [&](const String &line) {
        std::vector<String> args = splitDecl(line);

        LogInfo() << "Args: " << args;

        Animation ani;
        ani.animationName = args[(int)EIdxAni::name];
        ani.layer = atoi(args[(int)EIdxAni::layer].c_str());
        ani.nextAnimation = args[(int)EIdxAni::nextAni];
        ani.blendIn = atof(args[(int)EIdxAni::blendIn].c_str());
        ani.blendOut = atof(args[(int)EIdxAni::blendOut].c_str());

        ani.ascName = args[(int)EIdxAni::ASC_Name];
        ani.aniReversed = args[(int)EIdxAni::aniDir] == "R";
        ani.startFrame = atoi(args[(int)EIdxAni::startFrame].c_str());
        ani.endFrame = atoi(args[(int)EIdxAni::endFrame].c_str());

        ani.flags = 0;
        if(args[(int)EIdxAni::flags].find("m") != String::npos)
            ani.flags |= Animation::MoveObject;

        if(args[(int)EIdxAni::flags].find("r") != String::npos)
            ani.flags |= Animation::RotateObject;

        if(args[(int)EIdxAni::flags].find("e") != String::npos)
            ani.flags |= Animation::WaitEnd;

        if(args[(int)EIdxAni::flags].find("f") != String::npos)
            ani.flags |= Animation::Fly;

        if(args[(int)EIdxAni::flags].find("i") != String::npos)
            ani.flags |= Animation::Idle;

        m_Animations.push_back(ani);
    };

    /**
     * Base node
     */
    auto readModel = [&]() {

        while (parser.getSeek() < parser.getFileSize())
        {
            String line = parser.readLine(true);
            std::transform(line.begin(), line.end(), line.begin(), ::tolower);

            LogInfo() << "MDS-Line: " << line;

            if (line.find("//") != String::npos)
                continue; // Skip comments. These MUST be on their own lines, by definition.
            else if (line.find("anienum") != String::npos)
                continue;
            else if (line.find("aniblend") != String::npos)
                continue;
            else if (line.find("eventmmstartani") != String::npos)
                continue;
            else if (line.find("anialias") != String::npos)
                continue;
            else if (line.find("anicomb") != String::npos)
                continue;
            else if (line.find("anidisable") != String::npos)
                continue;
            else if (line.find("ani") != String::npos)
                readAni(line);
            else if (line.find("meshandtree") != String::npos)
                continue;
            else if (line.find("registermesh") != String::npos)
                continue;
            else if (line.find("startmesh") != String::npos)
                continue;
            else if (line.find("{") != String::npos)
                continue;
            else if (line.find("}") != String::npos)
                continue; //break; // There can be only one } per block
        }
    };

    while (parser.getSeek() < parser.getFileSize())
    {
        String line = parser.readLine(true);
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);

        LogInfo() << "MDS-Line: " << line;

        if (line.find("//") != String::npos)
            continue; // Skip comments. These MUST be on their own lines, by definition.
        else if (line.find("model") != String::npos)
            readModel();
    }
}
