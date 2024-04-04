#version 330 core

// Read in vertex attributes
layout (location = 0) in vec3 aPos; // vertex positions/Coordinates

// Replace these with camera abstraction
uniform mat4 camMatrix; // Cam = proj * view (not using moel rn cuz object is in center)

// Output these (such that fragment shader can access)
out vec2 texCoord;

// Assign
void main()
{
	// Order is important here, notice model -> view -> proj matrix
	gl_Position = camMatrix * vec4(aPos, 1.0);
}