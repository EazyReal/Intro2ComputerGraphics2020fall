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

  // Lambert's cosine law
  // If cos(N, L) < 0, theta is bigger than pi/2, the position cannot be illuminated
  float lambertian = max(dot(N, L), 0.0);
  float spec = 0.0;
  if(lambertian > 0.0) {
    vec3 R = normalize(reflect(-L, N));      // Reflected light vector
    vec3 V = normalize(-worldPos); // Vector to eye pos (0,0,0)
    // Compute the specular term
    float specAngle = max(dot(R, V), 0.0);
    spec = pow(specAngle, gloss);
  }
  vec4 obj_color = texture2D(texture, uv);
  vec4 ambient = vec4(La, 1.0) * vec4(La, 1.0) * obj_color;
  vec4 diffuse = vec4(Ld, 1.0) * vec4(Kd, 1.0) * obj_color * lambertian;
  vec4 specular = vec4(Ls, 1.0) * vec4(Ks, 1.0) * spec;
  color = ambient + diffuse + specular;
} 