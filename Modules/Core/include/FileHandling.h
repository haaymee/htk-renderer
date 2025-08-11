#pragma once

#include <string>
#include <filesystem>

namespace FileHandling
{
    /// 
    /// @param relativeFilePath the path of the file relative to the project root directory
    /// @return the full contents of a text file as a string
    std::string ReadTextFileAsString(const std::filesystem::path& relativeFilePath);

    bool DoesDirectoryExist(const std::filesystem::path& directoryPath);

    bool DoesFileExist(const std::filesystem::path& relativeFilePath);    
}






