# use Package Config first
find_package(PkgConfig)
if (PKG_CONFIG_FOUND)
	pkg_check_modules(OGRE OGRE)
	pkg_check_modules(OIS OIS)
	pkg_check_modules(RakNet RakNet)
	pkg_check_modules(QuickGUI QuickGUI)

	if (OGRE_FOUND)
		set(DEP_INCLUDE_PATH ${DEP_INCLUDE_PATH} ${OGRE_INCLUDE_DIRS})
		set(DEP_LIB_PATH ${DEP_LIB_PATH} ${OGRE_LIBRARY_DIRS})
	endif()

	if (OIS_FOUND)
		set(DEP_INCLUDE_PATH ${DEP_INCLUDE_PATH} ${OIS_INCLUDE_DIRS})
		set(DEP_LIB_PATH ${DEP_LIB_PATH} ${OIS_LIBRARY_DIRS})
	endif()
	
	if (RakNet_FOUND)
		set(DEP_INCLUDE_PATH ${DEP_INCLUDE_PATH} ${RakNet_INCLUDE_DIRS})
		set(DEP_LIB_PATH ${DEP_LIB_PATH} ${RakNet_LIBRARY_DIRS})	
	endif()

	if (QuickGUI_FOUND)
		set(DEP_INCLUDE_PATH ${DEP_INCLUDE_PATH} ${QuickGUI_INCLUDE_DIRS})
		set(DEP_LIB_PATH ${DEP_LIB_PATH} ${QuickGUI_LIBRARY_DIRS})	
	endif()
endif()

# Find packages manually

# Find OGRE
if (NOT OGRE_FOUND)
	message("-- Manualy looking for ogre")

	# Set Search Paths
	if (WIN32)
		# Windows Search Paths
		set(TMP_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/sdk/include ${CMAKE_SOURCE_DIR}/sdk/include/OGRE)
		set(TMP_LIB_PATH ${CMAKE_SOURCE_DIR}/sdk/lib)
		set(TMP_LIBD_PATH ${TMP_LIB_PATH})
	elseif (UNIX)
		# Linux Search Paths
		set(TMP_INCLUDE_PATH /usr/include /usr/include/OGRE /usr/local/include /usr/local/include/OGRE)
		set(TMP_LIB_PATH /usr/lib /usr/local/lib )
		set(TMP_LIBD_PATH ${TMP_LIB_PATH})
	endif()
	if (APPLE)
		# Mac OS X Search Paths
	endif()
	
	find_path(OGRE_INCLUDE_DIR Ogre.h ${TMP_INCLUDE_PATH})
	find_library(OGRE_LIBRARY_REL NAMES OgreMain PATHS ${TMP_LIB_PATH})
	find_library(OGRE_LIBRARY_DBG NAMES OgreMain_d PATHS ${TMP_LIBD_PATH})
	if (OGRE_LIBRARY_REL AND OGRE_LIBRARY_DBG)
		message("--  Ogre lib found")
		set(OGRE_LIBRARIES optimized ${OGRE_LIBRARY_REL} debug ${OGRE_LIBRARY_DBG})
	elseif (OGRE_LIBRARY_REL)
		message("--  Ogre lib found")
		set(OGRE_LIBRARIES ${OGRE_LIBRARY_REL})
	elseif (OGRE_LIBRARY_DBG)
		message("--  Ogre lib found")		
		set(OGRE_LIBRARIES ${OGRE_LIBRARY_DBG})
	endif()	
	if (OGRE_INCLUDE_DIR AND OGRE_LIBRARIES)
		message("--  Ogre reolved")
		set(DEP_LIB_PATH ${DEP_LIB_PATH} ${TMP_LIB_PATH})
		set(DEP_INCLUDE_PATH ${DEP_INCLUDE_PATH} ${TMP_INCLUDE_PATH})
		set(OGRE_FOUND TRUE)
	endif()	
endif()

if (NOT OIS_FOUND)
	message("-- Manualy looking for OIS")

	# Set Search Paths
	if (WIN32)
		# Windows Search Paths
		set(TMP_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/sdk/include ${CMAKE_SOURCE_DIR}/sdk/include/OIS)
		set(TMP_LIB_PATH ${CMAKE_SOURCE_DIR}/sdk/lib )
		set(TMP_LIBD_PATH ${TMP_LIB_PATH})		
	elseif (UNIX)
		# Linux Search Paths
		set(TMP_INCLUDE_PATH /usr/include /usr/include/OIS /usr/local/include /usr/local/include/OIS)
		set(TMP_LIB_PATH /usr/lib /usr/local/lib )
		set(TMP_LIBD_PATH ${TMP_LIB_PATH})
	endif()
	if (APPLE)
		# Mac OS X Search Paths
	endif()
	# Find OIS
	find_path(OIS_INCLUDE_DIR OIS.h ${TMP_INCLUDE_PATH})
	find_library(OIS_LIBRARY_REL NAMES OIS PATHS ${TMP_LIB_PATH})
	find_library(OIS_LIBRARY_DBG NAMES OIS_d PATHS ${TMP_LIBD_PATH})
	if (OIS_LIBRARY_REL AND OIS_LIBRARY_DBG)
		message("--  OIS lib found")		
		set(OIS_LIBRARIES optimized ${OIS_LIBRARY_REL} debug ${OIS_LIBRARY_DBG})
	elseif (OIS_LIBRARY_REL)
		message("--  OIS lib found")
		set(OIS_LIBRARIES ${OIS_LIBRARY_REL})
	elseif (OIS_LIBRARY_DBG)
		message("--  OIS lib found")
		set(OIS_LIBRARIES ${OIS_LIBRARY_DBG})
	endif()	
	if (OIS_INCLUDE_DIR AND OIS_LIBRARIES)
		message("--  OIS resolved")
		set(DEP_LIB_PATH ${DEP_LIB_PATH} ${TMP_LIB_PATH})
		set(DEP_INCLUDE_PATH ${DEP_INCLUDE_PATH} ${TMP_INCLUDE_PATH})
		set(OIS_FOUND TRUE)
	endif()
endif()

if (NOT RakNet_FOUND)
	message("-- Manualy looking for raknet")

	# Set Search Paths
	if (WIN32)
		# Windows Search Paths
		set(TMP_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/sdk/include ${CMAKE_SOURCE_DIR}/sdk/include/raknet)
		set(TMP_LIB_PATH ${CMAKE_SOURCE_DIR}/sdk/lib)
		set(TMP_LIBD_PATH ${TMP_LIB_PATH})
	elseif (UNIX)
		# Linux Search Paths
		set(TMP_INCLUDE_PATH /usr/include /usr/include/raknet /usr/local/include /usr/local/include/raknet)
		set(TMP_LIB_PATH /usr/lib /usr/local/lib )
		set(TMP_LIBD_PATH ${TMP_LIB_PATH})
	endif()
	if (APPLE)
		# Mac OS X Search Paths
	endif()

	# Find raknet
	find_path(RakNet_INCLUDE_DIR RakPeer.h ${TMP_INCLUDE_PATH})
	find_library(RakNet_LIBRARY_REL NAMES raknet PATHS ${TMP_LIB_PATH})
	find_library(RakNet_LIBRARY_DBG NAMES raknet_d PATHS ${TMP_LIBD_PATH})
	if (RakNet_LIBRARY_REL AND RakNet_LIBRARY_DBG)
		message("--  raknet lib found")
		set(RakNet_LIBRARIES optimized ${RakNet_LIBRARY_REL} debug ${RakNet_LIBRARY_DBG})
	elseif (RakNet_LIBRARY_REL)
		message("--  raknet lib found")
		set(RakNet_LIBRARIES ${RakNet_LIBRARY_REL})
	elseif (RakNet_LIBRARY_DBG)
		message("--  raknet lib found")
		set(RakNet_LIBRARIES ${RakNet_LIBRARY_DBG})
	endif()	
	if (RakNet_INCLUDE_DIR AND RakNet_LIBRARIES)
		message("--  raknet resolved")
		set(DEP_LIB_PATH ${DEP_LIB_PATH} ${TMP_LIB_PATH})
		set(DEP_INCLUDE_PATH ${DEP_INCLUDE_PATH} ${TMP_INCLUDE_PATH})
		set(RakNet_FOUND TRUE)
	endif()
endif()

if (NOT QuickGUI_FOUND)
	message("-- Manualy looking for QuickGUI")

	# Set Search Paths
	if (WIN32)
		# Windows Search Paths
		set(TMP_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/sdk/include ${CMAKE_SOURCE_DIR}/sdk/include/QuickGUI)
		set(TMP_LIB_PATH ${CMAKE_SOURCE_DIR}/sdk/lib)
		set(TMP_LIBD_PATH ${TMP_LIB_PATH})
	elseif (UNIX)
		# Linux Search Paths
		# set(TMP_INCLUDE_PATH /usr/include /usr/include/QuickGUI /usr/local/include /usr/local/include/QuickGUI)
		set(TMP_INCLUDE_PATH /usr/include/QuickGUI)
		set(TMP_LIB_PATH /usr/lib /usr/local/lib )
		set(TMP_LIBD_PATH ${TMP_LIB_PATH})
	endif()
	if (APPLE)
		# Mac OS X Search Paths
	endif()

	# Find QuickGUI
	find_path(QuickGUI_INCLUDE_DIR QuickGUI.h ${TMP_INCLUDE_PATH})
	find_library(QuickGUI_LIBRARY_REL NAMES QuickGUI PATHS ${TMP_LIB_PATH})
	find_library(QuickGUI_LIBRARY_DBG NAMES QuickGUI_d PATHS ${TMP_LIBD_PATH})
	if (QuickGUI_LIBRARY_REL AND QuickGUI_LIBRARY_DBG)
		message("--  QuickGUI lib found")
		set(QuickGUI_LIBRARIES optimized ${QuickGUI_LIBRARY_REL} debug ${QuickGUI_LIBRARY_DBG})
	elseif (QuickGUI_LIBRARY_REL)
		set(QuickGUI_LIBRARIES ${QuickGUI_LIBRARY_REL})
		message("--  QuickGUI lib found")
	elseif (QuickGUI_LIBRARY_DBG)
		set(QuickGUI_LIBRARIES ${QuickGUI_LIBRARY_DBG})
		message("--  QuickGUI lib found")
	endif()	
	if (QuickGUI_INCLUDE_DIR AND QuickGUI_LIBRARIES)
		message("--  QuickGUI resolved")	
		set(DEP_LIB_PATH ${DEP_LIB_PATH} ${TMP_LIB_PATH})
		set(DEP_INCLUDE_PATH ${DEP_INCLUDE_PATH} ${TMP_INCLUDE_PATH})
		set(QuickGUI_FOUND TRUE)
	endif()
endif()
