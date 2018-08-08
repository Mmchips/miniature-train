#--------------------------------------------------------------------------
# example project
#--------------------------------------------------------------------------

PROJECT(S0008E_Lab2-Animation)
FILE(GLOB S0008E_Lab2-Animation_headers code/*.h)
FILE(GLOB S0008E_Lab2-Animation_sources code/*.cc)

SET(files_S0008E_Lab2-Animation ${S0008E_Lab2-Animation_headers} ${S0008E_Lab2-Animation_sources} code/Skeleton.cpp code/Skeleton.h code/Animation.cpp code/Animation.h)
SOURCE_GROUP("S0008E_Lab2-Animation" FILES ${files_S0008E_Lab2-Animation})

ADD_EXECUTABLE(S0008E_Lab2-Animation ${files_S0008E_Lab2-Animation})
TARGET_LINK_LIBRARIES(S0008E_Lab2-Animation core render tinyxml glut)
ADD_DEPENDENCIES(S0008E_Lab2-Animation core render)
