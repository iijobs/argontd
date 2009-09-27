# FIND boost
# SET 
# boost_INCLUDE_DIRS '-I'

if (NOT boost_FOUND)
	message("-- Manualy looking for boost")

	# Set Search Paths
	if (WIN32)
		set(boost_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/sdk/include ${CMAKE_SOURCE_DIR}/sdk/include/boost)
	#	set(boost_LIBRARY_DIRS ${CMAKE_SOURCE_DIR}/sdk/lib)
	else (WIN32)
		set(boost_INCLUDE_DIRS /usr/include/boost /usr/local/include/boost)
	#	set(boost_LIBRARY_DIRS /usr/lib /usr/local/lib )
	endif()
	
	find_path(boost_INCLUDE_DIR function.hpp ${boost_INCLUDE_DIRS})
	if (boost_INCLUDE_DIR)
		message("--  boost includes found")
	endif()

	#find_library(boost_LIBRARIES NAMES boost PATHS ${boost_LIBRARY_DIRS})
	#if (boost_LIBRARIES)
	#	message("--  boost lib found")
	#endif()

	if (boost_INCLUDE_DIR)
		message("--  boost resolved!")
		set(boost_FOUND TRUE)
	endif()	
endif()

if (NOT boost_FOUND)
	message(FATAL_ERROR "boost not found!")
endif()
