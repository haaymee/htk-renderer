# Linking GLAD to project
add_library(GLAD glad/src/glad.c)
target_include_directories(GLAD PUBLIC glad/include)

target_link_libraries(${PROJECT_NAME} PRIVATE GLAD)