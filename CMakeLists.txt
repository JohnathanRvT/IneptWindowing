cmake_minimum_required(VERSION 3.10)
project(IneptWindowing)

# Set the C++ standard to the latest available (currently C++20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DUNICODE /D_UNICODE")

# Recursively find all source and header files for IneptWindowing library
file(GLOB_RECURSE INEPTWINDOWING_SOURCES source/*.cpp)
file(GLOB_RECURSE INEPTWINDOWING_HEADERS include/*.h)

# Add the IneptWindowing library
add_library(IneptWindowing STATIC
    ${INEPTWINDOWING_SOURCES}
    ${INEPTWINDOWING_HEADERS}
)

add_subdirectory(libraries/IneptLogger)
add_subdirectory(libraries/glad)

# Add include directory for IneptWindowing library
target_include_directories(IneptWindowing PUBLIC include libraries/IneptLogger/include libraries/glad/include)

# Set output directories
set_target_properties(IneptWindowing PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")

# Set preprocessor defines
if(CMAKE_SYSTEM_NAME STREQUAL Windows)
  target_compile_definitions(IneptWindowing PRIVATE INEPT_PLATFORM_WINDOWS)
  # Find the opengl library
  find_package(OpenGL REQUIRED)
  # Link against the library
  target_link_libraries(IneptWindowing OpenGL::GL IneptLogger glad)
elseif(CMAKE_SYSTEM_NAME STREQUAL Linux)
  target_compile_definitions(IneptWindowing PRIVATE INEPT_PLATFORM_LINUX)
 target_link_libraries(IneptWindowing PRIVATE IneptLogger glad) 
elseif(CMAKE_SYSTEM_NAME STREQUAL Android)
  target_compile_definitions(IneptWindowing PRIVATE INEPT_PLATFORM_ANDROID)
 target_link_libraries(IneptWindowing PRIVATE IneptLogger glad) 
endif()