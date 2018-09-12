
cmake_minimum_required(VERSION 2.6)
PROJECT(boost-asio-examples)

# Usage: 
#   cmake .. -DCMAKE_INCLUDE_PATH=/home/ott/exp/include -DCMAKE_LIBRARY_PATH=/home/ott/exp/lib
#       -DBOOST_INCLUDEDIR=/home/ott/exp/include -DBOOST_LIBRARYDIR=/home/ott/exp/lib
#

add_definitions(-std=c++11 -pthread -lpthread)

SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE(Boost 1.42.0 REQUIRED COMPONENTS system thread regex)
find_package(OpenCV REQUIRED)
IF(Boost_FOUND)
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})
  LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY} ${OpenCV_LIBRARIES} pthread)

ADD_EXECUTABLE(server server.cpp structs.h MultiClientServer.h MultiClientServer.inl)
TARGET_LINK_LIBRARIES(server ${USED_LIBS})

target_include_directories(server PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(server LINK_PUBLIC ${OpenCV_LIBS})

ADD_EXECUTABLE(client client.cpp structs.h)
TARGET_LINK_LIBRARIES(client ${USED_LIBS})
target_include_directories(client PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(client LINK_PUBLIC ${OpenCV_LIBS})

