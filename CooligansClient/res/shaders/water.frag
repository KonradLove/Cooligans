#version 420 core

in vec3 vNormal;
in vec2 vTexCoord;
in vec3 vColor;

layout(binding = 0) uniform sampler2D texSampler;

uniform float time;

out vec4 outputColor;

in float offset;
in vec3 pos;

vec3 sunDir = vec3(0.3,0.6,0.4);
float PI = 3.141592653;
float rand(vec2 pos){
    return fract(sin(dot(pos,vec2(12.9898,78.233)))*43758.5453);
}

float noise(vec2 p, float freq ){
	float unit = 1.0/freq;
	vec2 ij = floor(p/unit);
	vec2 xy = mod(p,unit)/unit;
	//xy = 3.*xy*xy-2.*xy*xy*xy;
	xy = .5*(1.-cos(PI*xy));
	float a = rand((ij+vec2(0.,0.)));
	float b = rand((ij+vec2(1.,0.)));
	float c = rand((ij+vec2(0.,1.)));
	float d = rand((ij+vec2(1.,1.)));
	float x1 = mix(a, b, xy.x);
	float x2 = mix(c, d, xy.x);
	return mix(x1, x2, xy.y);
}

float pNoise(vec2 p, int res){
	float persistance = .5;
	float n = 0.;
	float normK = 0.;
	float f = 4.;
	float amp = 1.;
	int iCount = 0;
	for (int i = 0; i<50; i++){
		n+=amp*noise(p, f);
		f*=2.;
		normK+=amp;
		amp*=persistance;
		if (iCount == res) break;
		iCount++;
	}
	float nf = n/normK;
	return nf*nf*nf*nf;
}
float noise(vec2 pos){
    return fract(sin(dot(pos,vec2(12.9898,78.233)))*43758.5453);
}
float transition(float x){
    return pow(x,2.5);
}
void main(){
    vec2 newTexCoords = vTexCoord*50.0;
    
    vec4 col1 = texture(texSampler,newTexCoords + vec2(-time/20.0,time/45.0));

    vec4 col2 = texture(texSampler,newTexCoords + vec2(time/20.0,time/35.0));
    vec4 waterCol = vec4(mix(col1,col2,0.6) + (offset)/7.0);
    outputColor = mix(waterCol,vec4(0.25,0.23,0.42,1.0),transition(min(1.0,distance(vec3(0,0,0),pos)*1.2)));

}
