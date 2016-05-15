#version 330

uniform sampler2D myTextureSampler;
uniform vec4 ambientLightColor;

in vec2 UV;
in vec3 normal;

out vec4 color;

void main() {

    vec4 fragColor = texture( myTextureSampler, UV);
    fragColor = fragColor * ambientLightColor;
    color = fragColor;

}
