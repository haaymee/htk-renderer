include(${CMAKE_SOURCE_DIR}/CMake/files-collector.cmake)

set(LIBRARY_NAME Core)

collect_source_files(SOURCES ${CMAKE_CURRENT_SOURCE_DIR} RECURSIVE EXTENSIONS h cpp ixx)

if (SOURCES)
    add_library(${LIBRARY_NAME} ${SOURCES})

    target_compile_features(${LIBRARY_NAME} PUBLIC cxx_std_20)

    target_include_directories(${LIBRARY_NAME}
        PUBLIC include
        PRIVATE source exports
    )

    target_link_libraries(${LIBRARY_NAME} PUBLIC glm::glm SDL GLAD)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARY_NAME})

    # Set compile-definitions for project
    target_compile_definitions(${LIBRARY_NAME} PUBLIC PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")
endif()