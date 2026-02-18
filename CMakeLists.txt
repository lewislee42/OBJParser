# CMake file was originally copied from youtuber Erik Yuzwa (https://www.youtube.com/watch?v=_i4wRjcp8eU)

cmake_minimum_required(VERSION 4.1)

project(OBJParser CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set (CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# Source files
set(SOURCES 
  ./srcs/glad.c
  ./srcs/main.cpp
  ./srcs/Utils.cpp
  ./srcs/Shader.cpp
  ./srcs/ShaderProgram.cpp
  ./srcs/MainScene.cpp
)

include(FetchContent)
function(include_dependency libName gitUrl gitTag)
  FetchContent_Declare(${libName}
    GIT_REPOSITORY  ${gitUrl}
    GIT_TAG         ${gitTag}
    GIT_SHALLOW     TRUE
    GIT_PROGRESS    TRUE
  )
  FetchContent_MakeAvailable(${libName})
endFunction()

set(LIB1 glfw)
find_package(${LIB1} QUIET)
if (NOT ${LIB1}_FOUND)
  include_dependency(${LIB1} https://github.com/glfw/glfw.git 3.4)
endif()


add_executable(OBJParser ${SOURCES} ${IMGUI_SOURCES})

target_include_directories(OBJParser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes)

target_link_libraries(OBJParser PRIVATE ${LIB1})

