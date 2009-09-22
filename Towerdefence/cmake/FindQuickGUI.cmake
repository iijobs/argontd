# FIND QuickGUI
# SET 
# QuickGUI_INCLUDE_DIRS '-I'
# QuickGUI_LIBRARY_DIRS '-L'
# QuickGUI_LIBRARIES the '-l'

find_package(PkgConfig)
if (PKG_CONFIG_FOUND)
	message("-- looking for QuickGUI using PKG")
	pkg_check_modules(QuickGUI QuickGUI)
endif()

if (NOT QuickGUI_FOUND)
	message("-- Manualy looking for QuickGUI")

	# Set Search Paths
	if (WIN32)
		set(QuickGUI_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/sdk/include ${CMAKE_SOURCE_DIR}/sdk/include/QuickGUI)
		set(QuickGUI_LIBRARY_DIRS ${CMAKE_SOURCE_DIR}/sdk/lib)
	else (WIN32)
		set(QuickGUI_INCLUDE_DIRS /usr/include/QuickGUI /usr/local/include/QuickGUI)
		set(QuickGUI_LIBRARY_DIRS /usr/lib /usr/local/lib )
	endif()
	
	find_path(QuickGUI_INCLUDE_DIR QuickGUI.h ${QuickGUI_INCLUDE_DIRS})
	if (QuickGUI_INCLUDE_DIR)
		message("--  QuickGUI includes found")
	endif()

	find_library(QuickGUI_LIBRARIES NAMES QuickGUI PATHS ${QuickGUI_LIBRARY_DIRS})
	if (QuickGUI_LIBRARIES)
		message("--  QuickGUI lib found")
	endif()

	if (QuickGUI_INCLUDE_DIR AND QuickGUI_LIBRARIES)
		message("--  QuickGUI resolved!")
		set(QuickGUI_FOUND TRUE)
	endif()	
endif()

if (NOT QuickGUI_FOUND)
	message(FATAL_ERROR "QuickGUI not found!")
endif()
