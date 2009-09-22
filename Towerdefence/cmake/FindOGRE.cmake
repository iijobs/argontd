# FIND OGRE
# SET 
# OGRE_INCLUDE_DIRS '-I'
# OGRE_LIBRARY_DIRS '-L'
# OGRE_LIBRARIES the '-l'

find_package(PkgConfig)
if (PKG_CONFIG_FOUND)
	message("-- looking for ogre using PKG")
	pkg_check_modules(OGRE OGRE)
endif()

if (NOT OGRE_FOUND)
	message("-- Manualy looking for ogre")

	# Set Search Paths
	if (WIN32)
		set(OGRE_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/sdk/include ${CMAKE_SOURCE_DIR}/sdk/include/OGRE)
		set(OGRE_LIBRARY_DIRS ${CMAKE_SOURCE_DIR}/sdk/lib)
	else (WIN32)
		set(OGRE_INCLUDE_DIRS /usr/include/OGRE /usr/local/include/OGRE)
		set(OGRE_LIBRARY_DIRS /usr/lib /usr/local/lib )
	endif()
	
	find_path(OGRE_INCLUDE_DIR Ogre.h ${OGRE_INCLUDE_DIRS})
	if (OGRE_INCLUDE_DIR)
		message("--  Ogre includes found")
	endif()

	find_library(OGRE_LIBRARIES NAMES OgreMain PATHS ${OGRE_LIBRARY_DIRS})
	if (OGRE_LIBRARIES)
		message("--  Ogre lib found")
	endif()

	if (OGRE_INCLUDE_DIR AND OGRE_LIBRARIES)
		message("--  Ogre resolved!")
		set(OGRE_FOUND TRUE)
	endif()	
endif()

if (NOT OGRE_FOUND)
	message(FATAL_ERROR "OGRE not found!")
endif()