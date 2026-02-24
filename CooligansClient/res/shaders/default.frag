#version 420 core

in vec3 vNormal;
in vec2 vTexCoord;
in vec3 vColor;

in vec3 pos;

layout(binding = 0) uniform sampler2D texSampler;

uniform float time;

uniform vec3 objectPosition;

out vec4 outputColor;

vec3 sunDir = vec3(0.3,0.6,0.4);

float noise(vec2 pos){
    return fract(sin(dot(pos,vec2(12.9898,78.233)))*43758.5453);
}
float transition(float x){
    return pow(x,2.0);
}
void main(){
    float dotProd = min(1.0,dot(normalize(vNormal),sunDir)*2.0)-0.2;
    outputColor = vec4(texture(texSampler,vTexCoord)*max(dotProd,0.5));
    
    outputColor = mix(outputColor,vec4(0.25,0.23,0.42,1.0),transition(min(1.0,distance(objectPosition.xz,vec2(48.0,48.0))/250.0)))*1.25;
    
    //float blend = (sin(time/4.0)+1.0) * (1.0+outputColor.r);
    /*vec2 blendPos = vec2(gl_FragCoord.x-1920.0/2.0, gl_FragCoord.y-1080.0/2.0);
    vec2 blendPos = (vTexCoord-0.5)*1000.0;
    blendPos = floor(blendPos/((distance(blend,1.0)*7.0+1.0)));
    
    if(blend < 1.0){
        float ns = noise(blendPos);
        if(ns>blend) discard;
    }*/
}