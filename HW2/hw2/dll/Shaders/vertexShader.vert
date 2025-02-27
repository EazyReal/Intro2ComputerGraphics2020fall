﻿#version 430

//// TODO: ////
//
// Hint:
// 1. Receive position, normal, texcoord from bind buffer
// 2. Receive Model matrix, View matrix, and Projection matrix from uniform
// 3. Pass texcoord and Normal to fragment shader (normal will not use in this homework)
// 4. Calculate view space by gl_Position (must be vec4)

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in vec3 noral;

uniform mat4 Projection;
uniform mat4 M;
uniform mat4 View;

//pass to fragment shader
out vec2 texcoord_frag;
out vec3 noral_frag;

void main()
{
  gl_Position = Projection * View * M * vec4(position, 1.0);
  texcoord_frag = texcoord;
  noral_frag = noral;
}
