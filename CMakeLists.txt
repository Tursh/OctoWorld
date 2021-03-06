cmake_minimum_required(VERSION 3.18)

#Set constants
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_CXX_STANDARD 17)

#Set the output directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")


add_subdirectory(CGE)

project(OctoWorld)

include_directories(include)

include_directories(CGE/include)
link_libraries(CGE)

if (NOT WIN32)
    link_libraries(GL harfbuzz)
else ()
    link_libraries(opengl32)
endif ()

if (NOT BUILD_SHARED_LIBS)
    if (NOT WIN32)
        link_libraries(freetype GLEW glfw tinyxml2 pthread)
    else ()
        link_libraries(freetype glew32 glfw3 tinyxml2)
    endif ()
endif ()


add_executable(OctoWorld
        src/Main.cpp
        src/States/DebugState.cpp
        src/World/World.cpp)

add_custom_command(TARGET OctoWorld PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:OctoWorld>/res)