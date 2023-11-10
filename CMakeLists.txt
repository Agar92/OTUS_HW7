cmake_minimum_required(VERSION 3.9)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
set(PROJECT_NAME "bulk" CACHE STRING "Project name")
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION})
configure_file(version.h.in version.h)

set(SOURCES main.cpp  Interpreter.cpp)
set(HEADERS Interpreter.h)

add_executable(bulk ${SOURCES} ${HEADERS})

#this is necessary to switch off the g++ warning:
#warning: comma-separated list in using-declaration only available with '-std=c++17' or '-std=gnu++17'
#    4 | using std::string, std::getline;
#set(CMAKE_CXX_COMPILER_FLAGS "${CMAKE_CXX_COMPILER_FLAGS} -std=c++17")
#does not help!!!
#The lines
#set_target_properties(${PROJECT_NAME} PROPERTIES
#            	    CMAKE_CXX_STANDARD 17
#                     CMAKE_CXX_STANDARD_REQUIRED ON)
#do not help also!!!
#Only this line removes that annoying warning: 
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

set_target_properties(${PROJECT_NAME} PROPERTIES
            	    CMAKE_CXX_STANDARD 17
                      CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CPACK_GENERATOR "DEB")
SET(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
SET(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "agar10@yandex.ru")
INCLUDE(CPack)
