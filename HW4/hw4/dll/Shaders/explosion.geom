#version 430


layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;


//pass time
uniform float time;

// params
float magnitude = 2.0;
float speed = 0.001;
float magnitude_grav = 2.0;
float floor_coor = -10;
vec3 grav = vec3(0, -1, 0);


// color related
in VS_OUT {
    vec2 uv;
} gs_in[];

//uniform sampler2D texture;
out vec2 uv;
//out vec4 color;


vec3 get_normal()
{
   vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
   vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
   return normalize(cross(a, b));
}   

vec4 explode(vec4 position, vec3 normal)
{
    vec3 direction = normal * ((sin(time*speed) + 1.0) / 2.0) * magnitude; 
    return position + vec4(direction, 0.0);
}

vec4 gravity(vec4 position, vec3 grav)
{
    vec4 position2 =  position + vec4(magnitude_grav*grav*sin(time*speed)*sin(time*speed), 0.0);
    position2.y = max(floor_coor, position2.y);
    return position2;
}


void main()
{    
    // get the normal vector of the primitive
    vec3 normal = get_normal();

    // for each vertex, move to the direction of the normal (explode) for a little bit
    // and use gravity to -y a little bit
    gl_Position = explode(gl_in[0].gl_Position, normal);
    gl_Position = gravity(gl_Position, grav);
    uv = gs_in[0].uv;
    //color = texture2D(texture, uv);
    EmitVertex();

    gl_Position = explode(gl_in[1].gl_Position, normal);
    gl_Position = gravity(gl_Position, grav);
    uv = gs_in[1].uv;
    //color = texture2D(texture, uv);
    EmitVertex();

    gl_Position = explode(gl_in[2].gl_Position, normal);
    gl_Position = gravity(gl_Position, grav);
    uv = gs_in[2].uv;
    //color = texture2D(texture, uv);
    EmitVertex();

    EndPrimitive();
}  