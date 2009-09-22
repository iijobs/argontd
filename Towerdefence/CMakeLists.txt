# Basic Variables
cmake_minimum_required(VERSION 2.4)
project(TowerDefence)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

# find Packages in module
find_package(OGRE)
find_package(OIS)
find_package(QuickGUI)
# find_package(Newton)
# find_package(OgreNewt)
find_package(RakNet)

# Compile settings for build types
SET(CMAKE_CXX_FLAGS "")
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 -fno-inline")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g3")
SET(CMAKE_CXX_FLAGS_RELEASE "-O2")
SET(CMAKE_CXX_FLAGS_MINSIZEREL "-Os")

# Build Targets
# add_subdirectory(TerrainPhysics)
add_subdirectory(TowerDefence)
