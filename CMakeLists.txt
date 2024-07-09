cmake_minimum_required(VERSION 3.29)

# If CMake is less than required version, change policy to the currently installed CMake version and try anyway
if(${CMAKE_VERSION} VERSION_LESS 3.29)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(TerminalMomentum VERSION 1.0
                        DESCRIPTION "A note-taking cli application inspired by Notational Velocity"
                        LANGUAGES CXX)


############################################################
# Compile Step
############################################################

# Point CMake to cpp locations
set (SOURCES
    src/TerminalMomentum.cpp
    src/calc-example.cpp
)

# Add executeable that uses the set in $SOURCES
add_executable(terminalmomentum ${SOURCES})

# Include .h files for g++ (this is basically the -I dir arg)
target_include_directories(terminalmomentum
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)

############################################################
# Installation Step
############################################################

# Binary
install (TARGETS terminalmomentum
    DESTINATION bin)

# Config file
install (FILES config/terminalmomentum.conf
    DESTINATION etc)