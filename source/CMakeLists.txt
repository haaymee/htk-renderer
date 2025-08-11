file(GLOB_RECURSE SHADER_FILES "${CMAKE_SOURCE_DIR}/Source/Shaders/*.*")

# Temporary Add Shaders to IDE 
target_sources(${PROJECT_NAME} PRIVATE ${SHADER_FILES})
