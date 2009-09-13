# Build rules
include_directories(include)
file(GLOB TowerDefenceApp_SRC "src/*.cpp" "include/*.h")
add_executable(TowerDefenceApp ${TowerDefenceApp_SRC})

if (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
	set_target_properties(TowerDefenceApp PROPERTIES COMPILE_FLAGS "-fPIC ${COMPILE_FLAGS}")
elseif()
	set_target_properties(TowerDefenceApp PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})
endif()

target_link_libraries(TowerDefenceApp ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${RakNet_LIBRARIES} ${QuickGUI_LIBRARIES})

# Install rules
#install(TARGETS QuickGUI LIBRARY DESTINATION lib)
#install(FILES ${QUICKGUI_INCLUDE} DESTINATION include/QuickGUI)
#file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/QuickGUI.h "#include <QuickGUI/QuickGUI.h>\n")
#install(FILES QuickGUI.h DESTINATION include)

# Deal with Mac OS X's Framework system
#if (APPLE)
#  file(GLOB TowerDefenceApp_INCLUDE "include/*.h")
#  set_target_properties(QuickGUI PROPERTIES	FRAMEWORK TRUE)
#  set_target_properties(QuickGUI PROPERTIES PUBLIC_HEADER "${QUICKGUI_INCLUDE}")
#  set_target_properties(QuickGUI PROPERTIES	OUTPUT_NAME QuickGUI)
#  set_target_properties(QuickGUI
#     PROPERTIES BUILD_WITH_INSTALL_RPATH 1
#     INSTALL_NAME_DIR "@executable_path/../Frameworks"
#  )
#endif()
