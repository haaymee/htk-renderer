module;

#include <string>

export module Core:FileHandling;


/// 
/// @param relativeFilePath the path of the file relative to the project root directory
/// @return the full contents of a text file as a string
export std::string ReadTextFileAsString(const std::string& relativeFilePath);

export bool DoesDirectoryExist(const std::string& directoryPath);

export bool DoesFileExist(const std::string& relativeFilePath);




