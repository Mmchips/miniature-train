//
// Created by ivoako-5 on 3/21/18.
//

#include <GL/glew.h>

#ifndef GSCEPT_LAB_ENV_SHADER_H_H
const GLchar* vShade =
"#version 440\n"
"layout(location=0) in vec3 pos;\n"
"layout(location=1) in vec2 UV;\n"
"layout(location=2) in vec4 normal;\n"
"layout(location=3) in vec4 tangent;\n"
"layout(location=4) in vec4 biNormal;\n"
"layout(location=5) in vec4 skinWeight;\n"
"layout(location=6) in vec4 indice;\n"

"layout(location=0) out vec2 uv;\n"
"layout(location=1) out vec3 vertPos;\n"
"layout(location=2) out vec4 lightPosition;\n"
"uniform mat4 skeleton[21];\n"
"uniform mat4 rotation;\n"

"out vec3 color;\n"
"const int arr[21] = {19, 18, 17, 0, 20, 15, 13, 1, 12, 9, 2, 10, 3, 11, 14, 16, 4, 5, 8, 6, 7};\n"
"void main()\n"
"{\n"
"    uv.x = UV.x;\n"
"    uv.y = UV.y;\n"
"    mat4 joint = skeleton[arr[int(indice[0])]] * skinWeight[0] +\n"
"    skeleton[arr[int(indice[1])]] * skinWeight[1] +\n"
"    skeleton[arr[int(indice[2])]] * skinWeight[2] +\n"
"    skeleton[arr[int(indice[3])]] * skinWeight[3];\n"
"    vec4 newPosition = rotation * joint * vec4(pos, 1.0f);\n"
"    newPosition.x *=0.3;\n"
"    newPosition.y *=0.3;\n"
"    newPosition.z *=0.3;\n"
"    vec4 T = rotation * joint * normalize(tangent);\n"
"    vec4 B = rotation * joint * normalize(biNormal);\n"
"    vec4 N = rotation * joint * normalize(normal);\n"
"    gl_Position = newPosition;\n"
"    mat3 TBN = transpose(mat3(vec3(T), vec3(B), vec3(N)));\n"
"    lightPosition = vec4(TBN*vec3(0,0,2),1.0);\n"
"    vertPos = TBN * (vec3(newPosition)/newPosition.w);\n"
"};\n";

const GLchar* fShade =
"#version 440\n"
"layout(location=0) in vec2 UV;\n"
"layout(location=1) in vec3 verticePos;\n"
"layout(location=2) in vec4 lightningPosition;\n"
"out vec3 Color;\n"
"uniform sampler2D diffuseTex;\n"
"uniform sampler2D normalTex;\n"
"uniform sampler2D specTex;\n"
"const vec3 ambientColor = vec3(0.1, 0.1, 0.1);\n"
"const vec3 diffuseColor = vec3(0.4, 0.4, 0.4);\n"
"const float shininess = 22.0;\n"
"uniform float screenGamma = 2.2;\n"
"void main()\n"
"{\n"
"   vec3 specularColor = normalize(texture(specTex, UV).rgb);\n"
"   vec3 normal = normalize(texture(normalTex, UV).rgb * 2.0 -1.0);\n"
"   vec3 lightDir = normalize(vec3(lightningPosition) - verticePos);\n"
"   float lambertian = max(dot(lightDir,normal), 0.0);\n"
"   float specular = 0.0f;\n"

"   if(lambertian > 0.0)\n"
"   {\n"
"       vec3 viewDir = normalize(-verticePos);\n"
"       vec3 halfDir = normalize(lightDir + viewDir);\n"
"       float specAngle = max(dot(halfDir, normal), 0.0);\n"
"       specular = pow(specAngle, shininess);\n"
"   }\n"
"   vec3 colorLinear = ambientColor + lambertian * diffuseColor + specular * specularColor;\n"
"   vec3 colorGammaCorrected = pow(colorLinear, vec3(1.0/screenGamma));\n"
"   Color = texture(diffuseTex, UV).rgb * (ambientColor + lambertian) * specularColor;\n"
"}\n";

#define GSCEPT_LAB_ENV_SHADER_H_H

#endif //GSCEPT_LAB_ENV_SHADER_H_H
