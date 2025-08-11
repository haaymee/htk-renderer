function(collect_source_files OUTPUT_VAR SEARCH_DIRECTORY)
    # Parse optional arguments
    set(options RECURSIVE)
    set(oneValueArgs "")
    set(multiValueArgs EXTENSIONS EXCLUDE_PATTERNS)
    
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    
    # Default extensions if none provided
    if(NOT ARG_EXTENSIONS)
        set(ARG_EXTENSIONS cpp cxx cc c ixx)
    endif()
    
    set(ALL_FILES "")
    
    foreach(EXT ${ARG_EXTENSIONS})
        if(ARG_RECURSIVE)
            file(GLOB_RECURSE FILES "${SEARCH_DIRECTORY}/*.${EXT}")
        else()
            file(GLOB FILES "${SEARCH_DIRECTORY}/*.${EXT}")
        endif()
        list(APPEND ALL_FILES ${FILES})
    endforeach()
    
    # Remove excluded patterns
    if(ARG_EXCLUDE_PATTERNS)
        foreach(PATTERN ${ARG_EXCLUDE_PATTERNS})
            list(FILTER ALL_FILES EXCLUDE REGEX "${PATTERN}")
        endforeach()
    endif()
    
    set(${OUTPUT_VAR} ${ALL_FILES} PARENT_SCOPE)
endfunction()