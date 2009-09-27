#set include
include_directories("include" ${RakNet_INCLUDE_DIRS} ${boost_INCLUDE_DIRS} "/usr/include")

file(GLOB NetworkSystem_SRC "src/*.cpp" "include/*.h")

add_library(NetworkSystem STATIC ${NetworkSystem_SRC})




