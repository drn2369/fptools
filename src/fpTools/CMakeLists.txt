#Project
project(fpTools)

#List source files
FILE(GLOB_RECURSE LIBRARY_FILES_C "*.cpp*")
FILE(GLOB_RECURSE LIBRARY_FILES_H "*.h")

#Create library
add_library(fpTools ${LIBRARY_FILES_H} ${LIBRARY_FILES_C})


