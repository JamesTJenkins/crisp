#type vertex
#version 460 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec4 Color;
layout(location = 2) in vec2 Texcoord;
layout(location = 3) in float TextureIndex;

uniform mat4 u_ViewProjection;
//uniform mat4 u_Transform;

out vec4 v_Color;
out vec2 v_Texcoords;
out float v_TextureIndex;

void main() {
	v_Color = Color;
	v_Texcoords = Texcoord;
	v_TextureIndex = TextureIndex;
	//gl_Position = u_ViewProjection * u_Transform * vec4(Position, 1.0);
	gl_Position = u_ViewProjection * vec4(Position, 1.0);
}

#type fragment
#version 460 core
			
layout(location = 0) out vec4 color;
layout(location = 1) out int id;

in vec4 v_Color;
in vec2 v_Texcoords;
in float v_TextureIndex;

//uniform vec4 u_Color;
//uniform vec2 u_Tiling;
uniform sampler2D u_Textures[32];

void main() {
	//vec2 dx = dFdx(v_Texcoords);
	//vec2 dy = dFdy(v_Texcoords);
	//vec2 newCoords = u_Tiling * fract(v_Texcoords);
	//color = textureGrad(u_Texture[int(v_TextureIndex), newCoords, dx, dy) * u_Color;
	color = texture(u_Textures[int(v_TextureIndex)], v_Texcoords) * v_Color;
	id = 50;
}