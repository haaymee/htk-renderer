#include <string>
#include <filesystem>
#include <fstream>


module HTK:FileHandling;

namespace fs = std::filesystem;

const std::string& ReadTextFileAsString(const fs::path& relativeFilePath)
{
    std::ifstream file {relativeFilePath};

    if (!file)
        throw std::runtime_error("Failed to open text file: " + relativeFilePath.string());

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool DoesDirectoryExist(const std::string& directoryPath)
{
    
}

bool DoesFileExist(const std::string& relativeFilePath)
{
    
}
