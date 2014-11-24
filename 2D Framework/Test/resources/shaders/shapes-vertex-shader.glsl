#version 330

in vec4 position;
in vec4 colour;

out vec4 vColour;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

uniform vec4 vTintColour;

void main() 
{
	vColour = vTintColour;
	gl_Position = Projection * View * Model * position;
}