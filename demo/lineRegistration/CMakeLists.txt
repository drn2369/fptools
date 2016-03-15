#Project
project(demoReg)

#Get source
FILE(GLOB EXE_FILES_C "*.cpp")
FILE(GLOB EXE_FILES_H "*.h")

#Add executable
ADD_EXECUTABLE(demoReg ${EXE_FILES_H} ${EXE_FILES_C})

#Add dependency links
TARGET_LINK_LIBRARIES(demoReg fpTools fpTools_utility)
