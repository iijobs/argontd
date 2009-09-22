#set include
include_directories("include" ${OGRE_INCLUDE_DIRS} ${OIS_INCLUDE_DIRS} ${QuickGUI_INCLUDE_DIRS} ${RakNet_INCLUDE_DIRS})

#set link
link_directories ( ${OGRE_LIBRARY_DIRS} ${OIS_LIBRARY_DIRS} ${QuickGUI_LIBRARY_DIRS} ${RakNet_LIBRARY_DIRS} ) 

#executable
file(GLOB TowerDefenceApp_SRC "src/*.cpp" "include/*.h")
add_executable(TowerDefenceApp ${TowerDefenceApp_SRC})

target_link_libraries(TowerDefenceApp ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${RakNet_LIBRARIES} ${QuickGUI_LIBRARIES})



