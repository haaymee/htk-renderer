module;

#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

module Core:FileHandling;


namespace fs = std::filesystem;

std::string ReadTextFileAsString(const fs::path& relativeFilePath)
{
    std::ifstream file {PROJECT_ROOT_DIR / relativeFilePath};

    if (!file)
        throw std::runtime_error("Failed to open text file: " + relativeFilePath.string());

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool DoesDirectoryExist(const std::string& directoryPath)
{
    if (fs::exists(directoryPath))
        return fs::is_directory(directoryPath);

    std::cerr << __FILE__ << "\t" << __LINE__ << " __ Not a valid directory: " << directoryPath << "\n";
    return false;
}

bool DoesFileExist(const std::string& relativeFilePath)
{
    if (fs::exists(relativeFilePath))
        return fs::is_regular_file(relativeFilePath);

    std::cerr << __FILE__ << "\t" << __LINE__ << " __ File does not exist: " << relativeFilePath << "\n";
    return false;
}