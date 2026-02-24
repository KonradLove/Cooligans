#version 330 core

layout (location = 0) in vec3 aPosition;    //Vertex position
layout (location = 1) in vec3 aNormal;      //Normal direction
layout (location = 2) in vec2 aTexCoord;    //Texture Coordinate

uniform float time;

uniform mat4 model;                         //Transformation matrix
uniform mat4 projection;                    //Projection matrix
uniform mat4 view;                          //View Matrix

out vec3 vNormal;
out vec2 vTexCoord;

out vec3 pos;
out float offset;

float noise(vec2 pos){
    return fract(sin(dot(pos,vec2(12.9898,78.233)))*43758.5453);
}

void main(){
    vTexCoord = aTexCoord;
    mat4 mvp = projection * view * model;
    vec3 newPos = aPosition;

    offset = sin(time+noise(vTexCoord)*1000.0)/2.0;
    offset += cos(time+noise(vTexCoord+4.0)*1000.0)/4.0;
    newPos.y = newPos.y + offset/500.0;
    
    gl_Position = mvp * vec4(newPos,1.0);
    pos = aPosition;
}