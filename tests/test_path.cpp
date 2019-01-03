#include <utils/path.h>
#include <vdfs/fileIndex.h>
#include <gtest/gtest.h>
#include <utils/logger.h>

using namespace Utils;

int main(int argc, char** argv)
{
    VDFS::FileIndex::initVDFS(argv[0]);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(PATH, Test)
{
    Path test = "/dirA/dirB/file.ext";
    
    String directory = "/dirA/dirB";
    String filenameWE = "file.ext";
    String filename = "file";
    String extension = "ext";

    ASSERT_STREQ(filename.c_str(), test.getFilename().c_str());
    ASSERT_STREQ(extension.c_str(), test.getExtension().c_str());
    ASSERT_STREQ(filenameWE.c_str(), test.getFilenameWithExt().c_str());
    ASSERT_STREQ(directory.c_str(), test.getDirectory().c_str());
}

TEST(PATH, listFiles)
{
    Path path = "./../../ZenLib/tests/files";
    auto fileList = path.getFiles();

    for(auto &file : fileList)
        LogInfo() << "File: " << file;

    ASSERT_TRUE(fileList.size() > 0);
}

TEST(WPATH, Test)
{
    WPath test = L"/dirA/dirB/file.ext";

    WString directory = L"/dirA/dirB";
    WString filenameWE = L"file.ext";
    WString filename = L"file";
    WString extension = L"ext";

    ASSERT_STREQ(filename.c_str(), test.getFilename().c_str());
    ASSERT_STREQ(extension.c_str(), test.getExtension().c_str());
    ASSERT_STREQ(filenameWE.c_str(), test.getFilenameWithExt().c_str());
    ASSERT_STREQ(directory.c_str(), test.getDirectory().c_str());
}
