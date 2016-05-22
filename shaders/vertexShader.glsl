#version 330

uniform mat4 viewPerspectiveMatrix;
uniform mat4 modelMatrix;
layout (location = 0) in vec3 vertexPosition_modelspace;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexUV;

out vec3 vertex;
out vec2 UV;
out vec3 normal;
void main() {

    gl_Position = viewPerspectiveMatrix * modelMatrix * vec4(vertexPosition_modelspace, 1.0);

    vertex = vertexPosition_modelspace;
    UV = vertexUV;
    normal = vertexNormal;
}
