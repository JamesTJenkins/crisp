#type vertex
#version 460 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec4 Color;
layout(location = 2) in vec2 Texcoord;
layout(location = 3) in vec2 Tiling;
layout(location = 4) in float TextureIndex;
layout(location = 5) in int EntityID;

uniform mat4 u_ViewProjection;

out vec4 v_Color;
out vec2 v_Texcoords;
out vec2 v_Tiling;
out float v_TextureIndex;
out int v_EntityID;

void main() {
	v_Color = Color;
	v_Texcoords = Texcoord;
	v_Tiling = Tiling;
	v_TextureIndex = TextureIndex;
	v_EntityID = EntityID;
	gl_Position = u_ViewProjection * vec4(Position, 1.0);
}

#type fragment
#version 460 core
			
layout(location = 0) out vec4 color;
layout(location = 1) out int id;

in vec4 v_Color;
in vec2 v_Texcoords;
in vec2 v_Tiling;
in float v_TextureIndex;
flat in int v_EntityID;

uniform sampler2D u_Textures[32];

void main() {
	vec2 dx = dFdx(v_Texcoords);
	vec2 dy = dFdy(v_Texcoords);
	vec2 newCoords = v_Tiling * fract(v_Texcoords);
	color = textureGrad(u_Textures[int(v_TextureIndex)], newCoords, dx, dy) * v_Color;
	//color = texture(u_Textures[int(v_TextureIndex)], v_Texcoords) * v_Color;
	id = v_EntityID;
}