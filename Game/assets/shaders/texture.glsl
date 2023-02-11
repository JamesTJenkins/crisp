#type vertex
#version 460 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 Texcoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 v_Texcoords;

void main() {
	v_Texcoords = Texcoord;
	gl_Position = u_ViewProjection * u_Transform * vec4(Position, 1);
}

#type fragment
#version 460 core
			
layout(location = 0) out vec4 color;

in vec2 v_Texcoords;

uniform vec4 u_Color;
uniform vec2 u_Tiling;
uniform sampler2D u_Texture;

void main() {
	vec2 dx = dFdx(v_Texcoords);
	vec2 dy = dFdy(v_Texcoords);
	vec2 newCoords = u_Tiling * fract(v_Texcoords);
	color = textureGrad(u_Texture, newCoords, dx, dy) * u_Color;
}