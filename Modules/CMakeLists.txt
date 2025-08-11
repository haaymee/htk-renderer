set(MODULE_DIRS Core Graphics Utils)

foreach(DIR ${MODULE_DIRS})
    message(NOTICE "Processing Module... ${DIR}")
    add_subdirectory(${DIR})

    if (TARGET ${DIR})
        target_include_directories(${DIR} PUBLIC ${DIR}/include)
        set_target_properties(${DIR} PROPERTIES FOLDER "Engine Modules")
    endif()
endforeach()

