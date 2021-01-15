# Computer Graphics HW4


---

## Info
- Author: 0712238, Yan-Tong Lin
- Online Version: https://hackmd.io/WsfPWJZbRb6e5Wq6-I1u5g
- Environment
    - OS: Windows 10
- Execution
    - open `hw4.SIN` with `Visual Studio 2019 community` (Note: not VS Code) and press `F5` to run
- Femo video at https://youtu.be/P-bjPJ6jmis

---

## Explosion with Gravity
- The triagles of the object is applied two forces
    1. simulate the effect of explosion
        - direction = normal vector (of the primitive)
        - applied time = 0
        - position = position 
    2. simulate the effect of gravity force
        - direction = $-y$
        - applied time = always
- I add a floor at $y = -5$ to make primitives fall on it so that they will not fall forever.
- I use $\sin$ function to make it repeat
    - time is prassed by `glUniformPosition`
    - $t = \sin(t)*speed$ 
- Some setting (e.g. gravity, explosion force amplpitude) can be adjusted in geo shader

---

## Code Demo

### GetNormal
```
vec3 get_normal()
{
   vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
   vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
   return normalize(cross(a, b));
}   
```

### Explode 
```
vec4 explode(vec4 position, vec3 normal)
{
    vec3 direction = normal * ((sin(time*speed) + 1.0) / 2.0) * magnitude; 
    return position + vec4(direction, 0.0);
}
```


### Gravity
```
vec4 gravity(vec4 position, vec3 grav)
{
    vec4 position2 =  position + vec4(magnitude_grav*grav*sin(time*speed)*sin(time*speed), 0.0);
    position2.y = max(floor_coor, position2.y);
    return position2;
}
```

---

## Screenshots
- fail to load color from texture with primitive passing uv for some reason
![](https://i.imgur.com/UYla63i.png)

---

## References
- https://learnopengl.com/Advanced-OpenGL/Geometry-Shader