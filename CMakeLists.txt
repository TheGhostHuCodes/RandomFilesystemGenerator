CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(RandomFilesystemGenerator CXX)

FIND_PACKAGE(Boost 1.60 COMPONENTS program_options filesystem REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

IF(APPLE)
    ADD_COMPILE_OPTIONS(-stdlib=libc++ -std=c++11)
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -std=c++11 -stdlib=libc++ -lc++abi")
ENDIF(APPLE)

ADD_LIBRARY(utils utils.h utils.cpp)
TARGET_LINK_LIBRARIES(utils ${Boost_LIBRARIES})

ADD_EXECUTABLE(rfg main.cpp utils.h)
TARGET_LINK_LIBRARIES(rfg utils ${Boost_LIBRARIES})
