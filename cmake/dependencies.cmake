# Dependencies Directory
set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/ThirdParty")

include(FetchContent)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0af55cc
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(glm)

if(TARGET glm)
    set_target_properties(glm PROPERTIES FOLDER "Third Party")
endif()