#include "FileHandling.h"

#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

std::string FileHandling::ReadTextFileAsString(const fs::path& relativeFilePath)
{
    std::ifstream file {ConvertToAbsolutePath(relativeFilePath)};
    
    if (!file)
        throw std::runtime_error("Failed to open text file: " + relativeFilePath.string());

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool FileHandling::DoesDirectoryExist(const std::filesystem::path& directoryPath)
{
    auto path = ConvertToAbsolutePath(directoryPath);
    
    if (fs::exists(path))
        return fs::is_directory(path);

    std::cerr << __FILE__ << "\t" << __LINE__ << " __ Not a valid directory: " << path << "\n";
    return false;
}

bool FileHandling::DoesFileExist(const std::filesystem::path& relativeFilePath)
{
    auto path = ConvertToAbsolutePath(relativeFilePath);
    
    if (fs::exists(path))
        return fs::is_regular_file(path);

    std::cerr << __FILE__ << "\t" << __LINE__ << " __ File does not exist: " << path << "\n";
    return false;
}

std::filesystem::path FileHandling::ConvertToAbsolutePath(const std::filesystem::path& path)
{
    return PROJECT_ROOT_DIR / path;
}
