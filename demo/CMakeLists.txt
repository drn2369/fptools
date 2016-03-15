#Find Eigen and add to include
FIND_PACKAGE(Eigen3 REQUIRED)
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})

#Add subdir
ADD_SUBDIRECTORY(lineRegistration)
ADD_SUBDIRECTORY(minutiaeExtraction)
