#version 430
//// TODO ////
//
// Hint:
// 1. Recieve texcoord and Normal from vertex shader
// 2. Calculate and return final color to opengl
//

layout(binding = 0) uniform sampler2D objectTexture;
in vec2 texcoord_frag;
out vec4 outColor;

void main()
{
	outColor = texture2D(objectTexture, texcoord_frag);
}
