include(${CMAKE_SOURCE_DIR}/CMake/files-collector.cmake)

set(LIBRARY_NAME Graphics)

collect_source_files(SOURCES ${CMAKE_CURRENT_SOURCE_DIR} RECURSIVE EXTENSIONS h cpp ixx)

if (SOURCES)
    add_library(${LIBRARY_NAME} ${SOURCES})

    target_compile_features(${LIBRARY_NAME} PUBLIC cxx_std_20)

    target_include_directories(${LIBRARY_NAME}
        PUBLIC include
        PRIVATE source exports
    )

    target_link_libraries(${LIBRARY_NAME} PUBLIC glm::glm SDL GLAD)
    target_link_libraries(${LIBRARY_NAME} PRIVATE Core)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARY_NAME})
    
endif()

