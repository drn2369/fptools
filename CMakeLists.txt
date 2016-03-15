##############################################
# CMakeLists file for bulding fingerprintTools
#
#  David Nilosek 2015 
##############################################

#Cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)

#Project and versioning
PROJECT(fingerprintTools)
set(VERSION_MAJOR 0 CACHE STRING "Project major version number.")
set(VERSION_MINOR 0 CACHE STRING "Project minor version number.")
set(VERSION_PATCH 0 CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATH)

#Prevent in-source builds
IF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	message(FATAL_ERROR "In-source builds not allowed")
ENDIF()

SET(CMAKE_EXPORT_COMPILE_COMMANDS 1)

#Build Options
OPTION(BUILD_DOC "Build documentation" ON)
OPTION(BUILD_DEMO "Build demos" ON)

#Set Flags
SET(CMAKE_CXX_FLAGS_DEBUG, "-WAll -g")
SET(CMAKE_CXX_FLAGS_RELEASE, "-WAll -O3")

#Add source to include
SET(fingerprintTools_INCLUDE_DIRS
	"${CMAKE_SOURCE_DIR}/src"
	CACHE PATH "Include directories for fpTools")
INCLUDE_DIRECTORIES(${fingerprintTools_INCLUDE_DIRS})
	
#Add source
ADD_SUBDIRECTORY(src)

#Add demo
IF(BUILD_DEMO)
	#Add demo source
	ADD_SUBDIRECTORY(demo)
ENDIF()

#Build Doc
IF(BUILD_DOC)
	ADD_SUBDIRECTORY(doc)
ENDIF()
