# FIND RakNet
# SET 
# RakNet_INCLUDE_DIRS '-I'
# RakNet_LIBRARY_DIRS '-L'
# RakNet_LIBRARIES the '-l'

find_package(PkgConfig)
if (PKG_CONFIG_FOUND)
	message("-- looking for RakNet using PKG")
	pkg_check_modules(RakNet RakNet)
endif()

if (NOT RakNet_FOUND)
	message("-- Manualy looking for RakNet")

	# Set Search Paths
	if (WIN32)
		set(RakNet_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/sdk/include ${CMAKE_SOURCE_DIR}/sdk/include/RakNet)
		set(RakNet_LIBRARY_DIRS ${CMAKE_SOURCE_DIR}/sdk/lib)
	else (WIN32)
		set(RakNet_INCLUDE_DIRS /usr/include/RakNet /usr/local/include/RakNet)
		set(RakNet_LIBRARY_DIRS /usr/lib /usr/local/lib )
	endif()
	
	find_path(RakNet_INCLUDE_DIR RakPeer.h ${RakNet_INCLUDE_DIRS})
	if (RakNet_INCLUDE_DIR)
		message("--  RakNet includes found")
	endif()

	find_library(RakNet_LIBRARIES NAMES RakNet PATHS ${RakNet_LIBRARY_DIRS})
	if (RakNet_LIBRARIES)
		message("--  RakNet lib found")
	endif()

	if (RakNet_INCLUDE_DIR AND RakNet_LIBRARIES)
		message("--  RakNet resolved!")
		set(RakNet_FOUND TRUE)
	endif()	
endif()

if (NOT RakNet_FOUND)
	message(FATAL_ERROR "RakNet not found!")
endif()
