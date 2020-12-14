# Computer Graphics HW2

---

[TOC]

## Info
- Author: 0712238, Yan-Tong Lin
- Online Version: https://hackmd.io/3xeAp1AHTzGBpZawoP1kRg

---

## GLSL for drawing Umbreon

### Overview
- Shader Codes $\xrightarrow[\text{}]{\text{bind}}$ `program`
- Vectors $\xrightarrow[\text{}]{\text{bind}}$ `VBO` $\xrightarrow[\text{}]{\text{bind}}$ `VAO`
- Texture Graphics $\xrightarrow[\text{}]{\text{load}}$ `obj_texture`
- Data Vectors/MVP matrices $\xrightarrow[\text{}]{\text{pass with binding}}$ Vertex Shader $\xrightarrow[\text{}]{\text{texture coordinates}}$ Fragment Shader(texture is passed to here) $\xrightarrow[\text{}]{\text{}}$ Result

### Program Linking
![](https://i.imgur.com/2SBie27.png)

### VAO and VBO Binding
- bind three VBOs to a VAO
![](https://i.imgur.com/0PpOfNc.png =50%x)
- utilities for VBOs
        1. position vectors
        2. texture coordinates
        3. normal vectors
    
![](https://i.imgur.com/tH5T2xT.png)


### Texture Loading
![](https://i.imgur.com/IKfgXjJ.png)

### Code for Vertex Shader
- read in the parameters
- calculate `gl_Position`
- pass data required by the fragment shader (i.e. `texcoord_frag` and `normal`)
![](https://i.imgur.com/EIGWEx4.png)

### Code for Fragment Shader
- use 
    - texture object
    - texture coordinate (i.e. `texcoord_frag`) from vertex shader 
- to calculate 
    - color for each fragment
![](https://i.imgur.com/rBizwNs.png)

### Drawing with Shaders
- the params passing part
![](https://i.imgur.com/wVLHamC.png)


---

## Problems Encountered

1. `glUseprogram` has to be in front of all matrices binding (i.e. `glUniformMatrix4fv`) for them to be read in.
2. The order and the names of the variables passed to shaders (and from the vertex shader to the fragment shader) should be compatible.

---

## Bonus
- None

