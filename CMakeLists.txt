cmake_minimum_required(VERSION 3.25.1..3.29)

# If CMake is less than required version, change policy to the currently installed CMake version and try anyway
if(${CMAKE_VERSION} VERSION_LESS 3.29)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(TerminalMomentum VERSION 1.0
                        DESCRIPTION "A note-taking cli application inspired by Notational Velocity"
                        LANGUAGES CXX)

# Fetch libaries
include(FetchContent)

# FTXUI

find_package(ftxui)

# Download ftxui if it is not present on the system
if (NOT ftxui_FOUND)
    message(STATUS "ftxui package not found, will attempt to download and build ftxui from GitHub...")
    # set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE) # This prevent updating the dependancy
    FetchContent_Declare(ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
    GIT_TAG main # If we decide to not allow the project to use the latest version of ftxui then we can specify the version here
    )
    FetchContent_MakeAvailable(ftxui)
else()
    # FTXUI is already installed
    message(STATUS "ftxui package found, using the currently installed version.")
    include_directories(${ftxui_INCLUDE_DIRS})
endif()

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

# Links to ftxui
target_link_libraries(terminalmomentum
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
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