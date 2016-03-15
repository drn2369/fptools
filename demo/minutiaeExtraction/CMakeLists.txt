#Project
project(demoExtract)

#Get source
FILE(GLOB EXE_FILES_C "*.cpp")
FILE(GLOB EXE_FILES_H "*.h")

#Add executable
ADD_EXECUTABLE(demoExtract ${EXE_FILES_H} ${EXE_FILES_C})

#Add dependency links
TARGET_LINK_LIBRARIES(demoExtract fpTools fpTools_utility)
