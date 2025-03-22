#version 330 core

out vec3 color;

in vec3 fragmentColor;
in vec2 UV;

uniform sampler2D textureSampler;
uniform bool useTexture;

void main(){
	if (!useTexture){
		color = fragmentColor;
	}
	else{
		color = texture(textureSampler, UV).rgb;
	}
}
