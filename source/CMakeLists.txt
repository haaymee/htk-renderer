add_executable(HTK main.cpp)

target_link_libraries(HTK PRIVATE glm::glm)

# Set startup project (instead of ALL_BUILD)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT HTK)