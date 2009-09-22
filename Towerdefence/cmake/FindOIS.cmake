# FIND OIS
# SET 
# OIS_INCLUDE_DIRS '-I'
# OIS_LIBRARY_DIRS '-L'
# OIS_LIBRARIES the '-l'

find_package(PkgConfig)
if (PKG_CONFIG_FOUND)
	message("-- looking for OIS using PKG")
	pkg_check_modules(OIS OIS)
endif()

if (NOT OIS_FOUND)
	message("-- Manualy looking for OIS")

	# Set Search Paths
	if (WIN32)
		set(OIS_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/sdk/include ${CMAKE_SOURCE_DIR}/sdk/include/OIS)
		set(OIS_LIBRARY_DIRS ${CMAKE_SOURCE_DIR}/sdk/lib)
	else (WIN32)
		set(OIS_INCLUDE_DIRS /usr/include/OIS /usr/local/include/OIS)
		set(OIS_LIBRARY_DIRS /usr/lib /usr/local/lib )
	endif()
	
	find_path(OIS_INCLUDE_DIR OIS.h ${OIS_INCLUDE_DIRS})
	if (OIS_INCLUDE_DIR)
		message("--  OIS includes found")
	endif()

	find_library(OIS_LIBRARIES NAMES OIS PATHS ${OIS_LIBRARY_DIRS})
	if (OIS_LIBRARIES)
		message("--  OIS lib found")
	endif()

	if (OIS_INCLUDE_DIR AND OIS_LIBRARIES)
		message("--  OIS resolved!")
		set(OIS_FOUND TRUE)
	endif()	
endif()

if (NOT OIS_FOUND)
	message(FATAL_ERROR "OIS not found!")
endif()
