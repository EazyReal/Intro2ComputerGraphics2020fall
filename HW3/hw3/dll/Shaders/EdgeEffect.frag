#version 430

uniform sampler2D texture;

in vec2 uv;
in vec3 normal;
in vec3 worldPos;

uniform vec3 worldLightPos, worldCamPos;
uniform vec3 Ka, Kd, Ks, La, Ld, Ls;
uniform float gloss;
uniform vec4 edge_color;

out vec4 color;

void main()
{
  vec3 N = normalize(normal);
  vec3 V = normalize(worldCamPos-worldPos);
  // Edge Effect, Show Color When normal and view is almost orthogonal
  /*float level = dot(N, V);
  float intensity = 0.0;
  if(level < 0.05 && level > -0.05) {
    intensity = 1.0;
  }else{
    intensity = 0.0;
  }*/
  float intensity = exp(-10*abs(dot(N, V)));
  //vec4 obj_color = texture2D(texture, uv);
  color = intensity*edge_color;
} 