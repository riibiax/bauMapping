#version 410

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;


in vec4  position;
//in vec4  color;
//in vec3  normal;
in vec2  texcoord;

out vec2 vTexCoord;
out vec4 colorVarying;

void main() {
    vTexCoord = texcoord;
	gl_Position =  modelViewProjectionMatrix * position  ;
    
    //gl_PointSize = normal.x * 1.0;
    //colorVarying = color;
}