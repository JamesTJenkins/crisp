#type vertex
#version 460 core

layout(location = 0) in vec3 Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main() {
	gl_Position = u_ViewProjection * u_Transform * vec4(Position, 1);
}

#type fragment
#version 460 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main() {
	color = u_Color;
}