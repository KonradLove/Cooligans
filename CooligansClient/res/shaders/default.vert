#version 330 core

layout (location = 0) in vec3 aPosition;    //Vertex position
layout (location = 1) in vec3 aNormal;      //Normal direction
layout (location = 2) in vec2 aTexCoord;    //Texture Coordinate

uniform float time;

uniform mat4 model;                         //Transformation matrix
uniform mat4 projection;                    //Projection matrix
uniform mat4 view;                          //View Matrix

out vec3 vColor;
out vec3 vNormal;
out vec2 vTexCoord;

out vec3 pos;

void main(){
    vNormal = aNormal;
    vTexCoord = aTexCoord;
    mat4 mvp = projection * view * model;
    pos = (model * vec4(aPosition,1.0)).xyz;
    gl_Position = mvp * vec4(aPosition,1.0);
    vColor = vec3(aTexCoord,0.0);
}