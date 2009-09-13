# Basic Variables
cmake_minimum_required(VERSION 2.4)
project(TowerDefence)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules/")
set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin" CACHE STRING "")

#debug
option(DEBUG FALSE)
if (DEBUG)
	set(COMPILE_FLAGS "-g")
	set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin/" CACHE STRING "")
else()
	set(COMPILE_FLAGS "-w -s -Os -O3 -fexpensive-optimizations")
	set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin/" CACHE STRING "")
endif()

# find Packages in module
find_package(Dependencies)

#ogre
if (NOT OGRE_FOUND)
	message(FATAL_ERROR "OGRE not found!")
endif()

#OIS
if (NOT OIS_FOUND)
	message(FATAL_ERROR "OIS not found!")
endif()

#raknet
if (NOT RakNet_FOUND)
	message(FATAL_ERROR "RakNet not found!")
endif()

#QuickGUI
if ( NOT QuickGUI_FOUND)
	message(FATAL_ERROR "QuickGUI not found!")
endif()

#set include
include_directories(${DEP_INCLUDE_PATH})

#set link
link_directories (${DEP_LIB_PATH}) 

# all set up
# Build Targets
add_subdirectory(TowerDefence)
