# FIND OgreNewt
# SET 
# OgreNewt_INCLUDE_DIRS '-I'
# OgreNewt_LIBRARY_DIRS '-L'
# OgreNewt_LIBRARIES the '-l'

find_package(PkgConfig)
if (PKG_CONFIG_FOUND)
	message("-- looking for OgreNewt using PKG")
	pkg_check_modules(OgreNewt OgreNewt)
endif()

if (NOT OgreNewt_FOUND)
	message("-- Manualy looking for OgreNewt")

	# Set Search Paths
	if (WIN32)
		set(OgreNewt_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/sdk/include ${CMAKE_SOURCE_DIR}/sdk/include/OgreNewt)
		set(OgreNewt_LIBRARY_DIRS ${CMAKE_SOURCE_DIR}/sdk/lib)
	else (WIN32)
		set(OgreNewt_INCLUDE_DIRS /usr/include/OgreNewt /usr/local/include/OgreNewt)
		set(OgreNewt_LIBRARY_DIRS /usr/lib /usr/local/lib )
	endif()
	
	find_path(OgreNewt_INCLUDE_DIR OgreNewt.h ${OgreNewt_INCLUDE_DIRS})
	if (OgreNewt_INCLUDE_DIR)
		message("--  OgreNewt includes found")
	endif()

	find_library(OgreNewt_LIBRARIES NAMES OgreNewt PATHS ${OgreNewt_LIBRARY_DIRS})
	if (OgreNewt_LIBRARIES)
		message("--  OgreNewt lib found")
	endif()

	if (OgreNewt_INCLUDE_DIR AND OgreNewt_LIBRARIES)
		message("--  OgreNewt resolved!")
		set(OgreNewt_FOUND TRUE)
	endif()	
endif()

if (NOT OgreNewt_FOUND)
	message(FATAL_ERROR "OgreNewt not found!")
endif()
