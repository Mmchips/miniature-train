#--------------------------------------------------------------------------
# example project
#--------------------------------------------------------------------------

PROJECT(S0008E_Lab3-Skinning)
FILE(GLOB S0008E_Lab3-Skinning_headers code/*.h)
FILE(GLOB S0008E_Lab3-Skinning_sources code/*.cc)

SET(files_S0008E_Lab3-Skinning ${S0008E_Lab3-Skinning_headers} ${S0008E_Lab3-Skinning_sources} code/Skeleton.cpp code/Skeleton.h code/Animation.cpp code/Animation.h code/MeshResource.cpp code/MeshResource.h code/Skinning.h code/Skinning.cpp code/VertexComponent.h code/VertexComponent.cpp code/ShaderObject.h code/ShaderObject.cc code/Shader.h code/DDS_TYPES.h)
SOURCE_GROUP("S0008E_Lab3-Skinning" FILES ${files_S0008E_Lab3-Skinning})

ADD_EXECUTABLE(S0008E_Lab3-Skinning ${files_S0008E_Lab3-Skinning})
TARGET_LINK_LIBRARIES(S0008E_Lab3-Skinning core render tinyxml glut)
ADD_DEPENDENCIES(S0008E_Lab3-Skinning core render)

