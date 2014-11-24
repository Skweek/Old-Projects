#version 330

in vec4 position;
in vec2 texcoord;
in vec4 colour;

out vec4 vColour;
out vec2 vTexcoord;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main() 
{
	vColour = colour;
	vTexcoord = texcoord;
	gl_Position = Projection * View * Model * position;
}