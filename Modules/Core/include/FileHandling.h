#pragma once

#include <string>
#include <filesystem>

namespace FileHandling
{
    /// 
    /// @param relativeFilePath the path of the file relative to the project root directory
    /// @return the full contents of a text file as a string
    std::string ReadTextFileAsString(const std::filesystem::path& relativeFilePath);


    /// 
    /// @param directoryPath 
    /// @return True if the path relative to the root project directory is a valid directory.  
    bool DoesDirectoryExist(const std::filesystem::path& directoryPath);


    /// 
    /// @param relativeFilePath 
    /// @return True if the file relative to the project root directory exists.
    bool DoesFileExist(const std::filesystem::path& relativeFilePath);


    
    /// Converts a relative path to an absolute path based on the location of
    /// the project directory.
    /// @param outPath the relative file path to be converted into an absolute path
    /// @return 
    std::filesystem::path ConvertToAbsolutePath(const std::filesystem::path& outPath);
}






