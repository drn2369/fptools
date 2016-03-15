#Project
project(fpTools_utility)

#List source files
FILE(GLOB_RECURSE LIBRARY_FILES_C "*.cpp")
FILE(GLOB_RECURSE LIBRARY_FILES_H "*.h")

#Create library
add_library(fpTools_utility ${LIBRARY_FILES_H} ${LIBRARY_FILES_C})

#Define install
INSTALL(TARGETS fpTools_utility DESTINATION lib/fpTools EXPORT fingerprintTools-targets)
