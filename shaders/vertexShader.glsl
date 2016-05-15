#version 330

uniform mat4 ViewPerspectiveMatrix;
uniform mat4 ModelMatrix;
layout (location = 0) in vec3 vertexPosition_modelspace;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexUV;

out vec2 UV;
out vec3 normal;
void main() {

    gl_Position = ViewPerspectiveMatrix * ModelMatrix * vec4(vertexPosition_modelspace, 1.0);

    UV = vertexUV;
    normal = vertexNormal;
}
