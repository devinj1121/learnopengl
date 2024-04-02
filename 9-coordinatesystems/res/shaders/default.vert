#version 330 core

// Read in vertex attributes
layout (location = 0) in vec3 aPos; // vertex positions/Coordinates
layout (location = 1) in vec3 aColor; // vertex colors
layout (location = 2) in vec2 aTex; // vertex texture coordinates

// Controls the scale of the vertices
uniform float scale;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

// Output these (such that fragment shader can access)
out vec3 color; // We don't end up using since we use textures, but could
out vec2 texCoord;

// Assign
void main()
{
	// Order is important here, notice model -> view -> proj matrix
	gl_Position = proj * view * model *	vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
	color = aColor;
	texCoord = aTex;
}