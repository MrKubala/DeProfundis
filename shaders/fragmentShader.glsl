#version 330
#define MAX_LIGHTS 100

uniform sampler2D myTextureSampler;
uniform vec3 ambientLight;

in vec3 vertex;
in vec2 UV;

out vec4 color;

void main() {

   vec4 surfaceColor = texture(myTextureSampler, UV);

   vec3 linearColor = vec3(0);

   linearColor += surfaceColor.rgb * ambientLight;

   vec3 gamma = vec3(1.0/2.2);
   color = vec4(pow(linearColor, gamma), 1);
}

