# Dependencies Directory
set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/ThirdParty")

include(FetchContent)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0af55cc
    GIT_SHALLOW TRUE

    SOURCE_DIR ${FETCHCONTENT_BASE_DIR}/glm/source
    BINARY_DIR ${FETCHCONTENT_BASE_DIR}/glm/bin
)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG 96292a5
    GIT_SHALLOW TRUE

    SOURCE_DIR ${FETCHCONTENT_BASE_DIR}/SDL/source
    BINARY_DIR ${FETCHCONTENT_BASE_DIR}/SDL/bin
)

# Disable building the shared library
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
# Enable building the static library
set(SDL_STATIC ON CACHE BOOL "" FORCE)
# Disable building SDL3_test
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glm SDL3)

set_target_properties(glm PROPERTIES FOLDER "Third Party")

# Group SDL Targets under SDL
get_property(all_targets DIRECTORY ${FETCHCONTENT_BASE_DIR}/SDL/source PROPERTY BUILDSYSTEM_TARGETS)
foreach(t ${all_targets})
    set_target_properties(${t} PROPERTIES FOLDER "Third Party/SDL")
endforeach()

add_library(SDL ALIAS SDL3-static)