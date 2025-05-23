#version 330 core

out vec3 color;

in vec3 fragmentColor;
in vec2 UV;

uniform sampler2D textureSampler;
uniform float mixFactor;

void main(){
	vec3 texColor = texture(textureSampler, UV).rgb;
	color = mix(fragmentColor, texColor, mixFactor);
}
