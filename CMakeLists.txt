cmake_minimum_required(VERSION 3.24)

project(HTK
    VERSION 0.1
    DESCRIPTION "Hayme's graphics project"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/fetch-dependencies.cmake)

# Configure Predefined CMake Targets
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake Targets")

# Build Directory
set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build")

# Configurations Setup
if (CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Available build configuartions" FORCE)
    
    if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
        set(CMAKE_BUILD_TYPE Debug)
    endif()
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib") 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

foreach(CONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${CONFIG} CONFIG_UPPER)
    
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG_UPPER} 
        "${CMAKE_BINARY_DIR}/bin/${CONFIG}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIG_UPPER} 
        "${CMAKE_BINARY_DIR}/lib/${CONFIG}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIG_UPPER} 
        "${CMAKE_BINARY_DIR}/lib/${CONFIG}")
endforeach()

add_executable(HTK Source/main.cpp)
add_subdirectory(Dependencies)

# Set startup project (instead of ALL_BUILD)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT HTK)

# Set compile-definitions for project
add_compile_definitions(PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")