#--------------------------------------------------------------------------
# example project
#--------------------------------------------------------------------------

PROJECT(S0008E_Lab1-Skeleton)
FILE(GLOB S0008E_Lab1-Skeleton_headers code/*.h)
FILE(GLOB S0008E_Lab1-Skeleton_sources code/*.cc)

SET(files_S0008E_Lab1-Skeleton ${S0008E_Lab1-Skeleton_headers} ${S0008E_Lab1-Skeleton_sources} code/Skeleton.cpp code/Skeleton.h)
SOURCE_GROUP("S0008E_Lab1-Skeleton" FILES ${files_S0008E_Lab1-Skeleton})

ADD_EXECUTABLE(S0008E_Lab1-Skeleton ${files_S0008E_Lab1-Skeleton})
TARGET_LINK_LIBRARIES(S0008E_Lab1-Skeleton core render tinyxml glut)
ADD_DEPENDENCIES(S0008E_Lab1-Skeleton core render)
