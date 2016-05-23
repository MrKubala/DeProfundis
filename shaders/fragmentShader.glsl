#version 330
#define MAX_LIGHTS 100

uniform sampler2D myTextureSampler;
uniform vec3 cameraPosition;
uniform float materialSpecularPower;
uniform float materialSpecularIntensity;
uniform mat4 modelMatrix;
uniform vec3 ambientLight;
uniform vec3 ambientLight1;
uniform int numLights;

uniform struct Light {
   vec4 position;
   vec3 color;
   float attenuation;
   float coneAngle;
   vec3 coneDirection;
} lightsData[MAX_LIGHTS];

in vec3 vertex;
in vec2 UV;
in vec3 normal;

out vec4 color;

vec3 ApplyLight(Light light, vec3 surfaceColor, vec3 normal, vec3 surfacePos, vec3 surfaceToCamera) {
    vec3 surfaceToLight;
    float attenuation = 1.0;
    if(light.position.w == 0.0) {
        //directional light
        surfaceToLight = normalize(light.position.xyz);
        attenuation = 1.0; //no attenuation for directional lights
    } else {
        //point light
        surfaceToLight = normalize(light.position.xyz - surfacePos);
        float distanceToLight = length(light.position.xyz - surfacePos);
        attenuation = 1.0 / (1.0 + (light.attenuation * pow(distanceToLight, 2)));

        //cone restrictions (affects attenuation)
        float lightToSurfaceAngle = degrees(acos(dot(-surfaceToLight, normalize(light.coneDirection))));
        if(lightToSurfaceAngle > light.coneAngle){
            attenuation = 0.0;
        }
    }

    //diffuse
    float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
    vec3 diffuse = diffuseCoefficient * surfaceColor.rgb * light.color;

    //specular
    float specularIntensity = 0.0;
    if(diffuseCoefficient > 0.0){
        specularIntensity = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), materialSpecularPower);
        specularIntensity = specularIntensity * materialSpecularIntensity;
    }
    vec3 specular = specularIntensity * light.color;

    return attenuation * (diffuse + specular);
}

void main() {

   vec3 normal = normalize(transpose(inverse(mat3(modelMatrix))) * normal);
   vec3 surfacePos = vec3(modelMatrix * vec4(vertex, 1));
   vec4 surfaceColor = texture(myTextureSampler, UV);
   vec3 surfaceToCamera = normalize(cameraPosition - surfacePos);

   vec3 linearColor = vec3(0);
   //ambient
   linearColor += surfaceColor.rgb * ambientLight;

   for(int i = 0; i < numLights; ++i){
       linearColor += ApplyLight(lightsData[i], surfaceColor.rgb, normal, surfacePos, surfaceToCamera);
   }

   vec3 gamma = vec3(1.0/2.2);
   color = vec4(pow(linearColor, gamma), 1);
}

