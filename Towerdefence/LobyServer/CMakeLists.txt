#set include
include_directories("include" ${RakNet_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/Network/include "/usr/include")

file(GLOB Loby_SRC "src/*.cpp" "include/*.h")

add_library(Loby STATIC ${Loby_SRC})




