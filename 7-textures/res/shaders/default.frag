#version 330 core

in vec3 color;
in vec2 texCoord;

// Gets the texture objects from the program
uniform sampler2D tex0;
uniform sampler2D tex1;

uniform float mixtureFactor; // defaults as 0 if not set by program

// Outputs colors in RGBA
out vec4 FragColor;

void main()
{
	// Make the happy face flip over y axis (i.e., negative out the s)
	vec2 texCoord_xflipped;
	texCoord_xflipped = texCoord;
	texCoord_xflipped.x = -texCoord_xflipped.x;
	FragColor = mix(texture(tex0, texCoord), texture(tex1, texCoord_xflipped), mixtureFactor);
}