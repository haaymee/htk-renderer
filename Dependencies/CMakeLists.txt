# Linking GLAD to project
add_library(GLAD glad/src/glad.c)
target_include_directories(GLAD PUBLIC glad/include)
set_target_properties(GLAD PROPERTIES FOLDER "Third Party")

# Link fetched third party packages to project
target_link_libraries(HTK PRIVATE glm::glm SDL GLAD)
