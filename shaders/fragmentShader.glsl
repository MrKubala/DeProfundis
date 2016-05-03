#version 330

uniform sampler2D myTextureSampler;

in vec4 vertexColor;
in vec2 UV;

out vec4 color;

void main() {

    color = texture( myTextureSampler, UV);

}
