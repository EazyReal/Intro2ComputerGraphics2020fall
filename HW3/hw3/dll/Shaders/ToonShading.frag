#version 430

uniform sampler2D texture;

in vec2 uv;
in vec3 normal;
in vec3 worldPos;

uniform vec3 worldLightPos, worldCamPos;
uniform vec3 Ka, Kd, Ks, La, Ld, Ls;
uniform float gloss;

out vec4 color;

void main()
{
  vec3 N = normalize(normal);
  vec3 L = normalize(worldLightPos - worldPos);

  // Toon Shading considers cos(N,L)
  float level = dot(N, L);
  float intensity;
  if(level > 0.95) intensity = 1.0;
  else if(level > 0.75) intensity = 0.8;
  else if(level > 0.5) intensity = 0.6;
  else if(level > 0.25) intensity = 0.4;
  else intensity = 0.2;

  color = intensity * vec4(Kd, 1.0) * texture2D(texture, uv);
} 