#version 330

in vec4 position;
in vec2 texcoord;

out vec2 vTexcoord;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

uniform vec2 minUV;
uniform vec2 diffUV;

void main() {
	vTexcoord = texcoord * diffUV + minUV;
	gl_Position = Projection * View * Model * position;
}