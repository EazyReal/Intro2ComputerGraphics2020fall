#version 430

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 normal_in;
layout(location = 2) in vec2 texcoord;


uniform mat4 M, V, P;

out vec2 uv;
out vec3 normal;
out vec3 worldPos;

void main() {
  vec4 worldPos4 = V * M * vec4(in_position, 1.0);
  gl_Position = P * worldPos4;
  // position in the object space
  worldPos = vec3(worldPos4) / worldPos4.w;
  uv = texcoord;
  //calculate normal after translation
  normal = mat3(transpose(inverse(M))) * normal_in; 
}
