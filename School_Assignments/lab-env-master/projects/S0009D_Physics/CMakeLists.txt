#--------------------------------------------------------------------------
# example project
#--------------------------------------------------------------------------

PROJECT(S0009D_Physics)
FILE(GLOB S0009D_Physics_headers code/*.h)
FILE(GLOB S0009D_Physics_sources code/*.cc)

SET(files_S0009D_Physics ${S0009D_Physics_headers} ${S0009D_Physics_sources} code/MeshResource.cpp code/MeshResource.h code/stb_image.h code/Cube.cpp code/Cube.h code/RigidBody.cpp code/RigidBody.h code/CollisionHandler.cpp code/CollisionHandler.h)
SOURCE_GROUP("S0009D_Physics" FILES ${files_S0009D_Physics})

ADD_EXECUTABLE(S0009D_Physics ${files_S0009D_Physics})
TARGET_LINK_LIBRARIES(S0009D_Physics core render)
ADD_DEPENDENCIES(S0009D_Physics core render)
