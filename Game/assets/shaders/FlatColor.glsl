#type vertex
#version 460 core

layout(location = 0) in vec3 Position;

uniform mat4 vp;
uniform mat4 transform;

void main() {
	gl_Position = vp * transform * vec4(Position, 1);
}

#type fragment
#version 460 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main() {
	color = u_Color;
}