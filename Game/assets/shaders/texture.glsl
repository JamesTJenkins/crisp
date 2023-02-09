#type vertex
#version 460 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 Texcoord;

uniform mat4 vp;
uniform mat4 transform;

out vec2 tc;

void main() {
	tc = Texcoord;
	gl_Position = vp * transform * vec4(Position, 1);
}

#type fragment
#version 460 core
			
layout(location = 0) out vec4 color;

in vec2 tc;

uniform sampler2D u_Texture;

void main() {
	color = texture2D(u_Texture, tc);
}