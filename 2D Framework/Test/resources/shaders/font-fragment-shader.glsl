#version 330

in vec2 vTexcoord;
in vec4 vColour;

out vec4 outColor;

uniform sampler2D tex;

void main() 
{
	outColor = texture2D( tex, vec2( vTexcoord.x, 1 - vTexcoord.y ) ) * vColour;
}