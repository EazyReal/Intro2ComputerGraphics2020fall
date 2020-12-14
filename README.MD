# Introduction to Computer Graphics

## HWs
- HW1 requires no report 
    - with `MacOS` + `VSCode` + `CMake: QuickStart`
- [Computer Graphics HW2](/3xeAp1AHTzGBpZawoP1kRg)
    - with `Windows 10` + `Visual Studio` + `F5`

## TOC
[TOC]

---

## Graphics Systems (Start of Midterm)
![](https://i.imgur.com/IlMZ6L9.png =50%x)

### History
- 1990-
    - OpenGL API
- 2000-
    - Photorealism

### Introduction
- Elements of image formation
    - object
    - viewer
    - light sources
- CG basics
    - What makes 3D?
        - example: Vanishing points
    - Perspective projection
        - Synthetic Cameras
        - Pinhole
    - Represented by primitives 
        - curve/surfaces => polygon => triangles
    - Projections
    - Visibility
- A realistic 3D v
    - Delicate 3D models.
    - Perspective.
    - Hidden surface removal.
    - Shading (lighting & reflection).
    - Shadow
    - Detailed textures and normals
- Appendix - 3D movies
    - binocular cues

----

## Transformations

###  Affine transformation
- Affine transformation
    - preserve lines and parallelism 
- Translation
    - 3D affine => 4D linear
- Rotate
    - 2D
    - $R_z(\theta)$
    - care Ry
- Scaling
- Reflection
- Shear
- Matrix Multiplicatoin and Inverses


### General Rotation 
(row matrices notation)
- notation
    - ![](https://i.imgur.com/OZmM0Ip.png =40%x)
- different point 
    - $T_{point}^{-1}R(\theta)T_{point}$
- different axis
    - $R_{axis}^{-1}R_z(\theta)R_{axis}$

### Ordering
(column matrices notation)
- Instancing
    - $M=TRS$
- Hierarchical structure
    - ![](https://i.imgur.com/UOM6wGu.png =40%x)
    - ![](https://i.imgur.com/7ZmddLb.png =40%x)
- OpenGL Matrix Stack
    - ![](https://i.imgur.com/kddvsca.png =40%x)

### Appendix - 3D LA
- vector space
- affine space
    - vector space + point 
- parametric form
- convex property
    - asociated with parametric form is bounding
    - example
        - **Barycentric Coordinate**
- normal , dot/cross product
- dimension, basis, coordinate system
- frame
    - vector space + "the origin P0" 
    - Homogeneous Coordinates and Computer Graphics
        - 4d with w = 0 means vector, 1 means point
        - Homogeneous coordinates replaces points in three dimensions by lines through the origin in four dimensions.
- change of basis

----

## Projection

### Classic Viewing
- Viewing requires three basic elements
    - One or more objects
    - A viewer with a projection surface
    - Projectors that go from the object(s) to the projection surface
- Each object is assumed to constructed from flat principal faces
    - Buildings, polyhedra, manufactured objects
- Orthographic Projection
    - Projectors are orthogonal to projection surface

### Planar Geometric Projections
- project onto a plane
- Projectors are lines that either
    - converge at a center of projection
    - parallel
- preserve lines but not angles

Note: 
when need non-planar?

### Different Projections
https://sites.google.com/site/3d2dprojection/tou-ying-de-fen-lei
![](https://i.imgur.com/bf6ycBo.png)
- note: parallel => orthogonal
::: spoiler
![](https://i.imgur.com/2yWarGz.png)
![](https://i.imgur.com/Ww5nokV.png)
![](https://i.imgur.com/19qXBv7.png)
![](https://i.imgur.com/IUFpfW2.png)
![](https://i.imgur.com/dfzNjYG.png)
![](https://i.imgur.com/vihoQi3.png)
:::

### Computer Viewing
- Position the camera
    - model-view matrix
- Select a lens
    -  projection matrix
- Clip
    -  view volume
![](https://i.imgur.com/ObROJH6.png)


### Model-View (Change of Coordinate)
- gluLookAt(eye, at, up) //3d each
- coordinate change

### Orthogonal
- default orthographic projection
    - $M_{orth}$ ($I$ with 0 at z value)
- normalization for given value of box (clipping box)
    - clip to simplify calculation
    - the actually clipping will be cover later
    - given in l r of 3d
    - $M_{norm} = ST$, scaled to 2 by 2, move to origin
- general in 4d representation
    - $P = M_{orth}ST$
- oblique?
    - use shear Matrix to x, y axis, resp.
    - $P = M_{orth}ST H(\theta,\phi)$

### Perspective 
- simple 
    - COP at origin
    - projection plane at z=d, d<0
    - $M = \begin{pmatrix}1 & 0 & 0 &0 \\ 0 &1  & 0 & 0\\ 0&0  &1  &0 \\ 0& 0 & 1/d & 0\end{pmatrix}$
    - $p = Mq$
    - **Perspective Division**
- normalization of perspective
    - ![](https://i.imgur.com/A46TYge.png =40%x)
    - deduce to the case of orthogonal
    -  to use standard transformations in the pipeline and makes for efficient clipping
    -  for matrix plz see lecture notes
    -  
### Why Delay final “projection” until end?
- a single pipeline for both perspective and orthogonal viewing
- easier clipping
- *retain depth information* as long as possible
    - Hidden-Surface Removal
        - care numericle issues, since norm_pers is not isometric

### Viewport
- from working coordinate to the coordinate of display device
    - i.e. pixel (1920*1080)

### Recap (see lecture note pictures)
- load objs
- model transformations(M = TRS)
- camera transformation
- perspective + norm
    - do not do Perspective Division this step
- clipping
- projection + viewport
- Rasterization

----

## Shading
about light

### Factors
- Light sources
- Material properties
- Location of the viewer
- Surface orientation


### redering equations and global v.s. local
- global too hard => local approximation 
    - no inter-reflection, no refraction, no realistic shadow

### Light Sources
- point
- spot light
    - point with effective radius
- ambient light
    - Same amount of light everywhere in scene
    - Can model contribution of many sources and reflecting surfaces


### Phong Reflection Model
- 3 components
    - Ambient
    - Diffuse
    - Specular
- 4 vectors
    - To source l
    - To viewer v
    - Normal n
    - Perfect reflector r
- ideal reflector
    - $\vec{r} = 2(\vec{l} \cdot n)\vec{n}-\vec{l}$
- recap
    - $I = I_{ambient} + I_{diffuse} + I+{specular}$
    - $= k_{a}I_{a} + k_dI_d(l \cdot n) + k_sI_s(v \cdot r )^{\alpha}$

### Modified Phong (Blinn) Lighting Model
![](https://i.imgur.com/xRhqm12.png =40%x)
- approximate reflection faster
    - good in real-time apps
- halfway vector h
    - $h = \frac{l+v}{|l+v|}$
- so $(v \cdot r) ^\alpha$ replaced by $(n \cdot h) ^\beta$

### the vectors
- n is determined by user (in GLUT)
    - recap vector calculus
- l, v is known
- r can be given by n,l

### Polygonal Shading (!!)
- Flat Shading
    - const l,v,n for each polygon
- Gouraud Shading
    - average normal at each vertex
    - Phong lighting model at each vertex
    - Interpolate vertex shades across each polygon
    -  點向量 算shading 內插求值
- Phong Shading
    -  Find vertex normals
    -  Interpolate vertex normals across edges
    -  Find shades along edges
    -  Interpolate edge shades across polygons
    -  點向量 內插求法向量 再算shading
- Problems about Interpolated Shading
    - polygonal silhouette(輪廓)
    - Perspective distortion
    - Orientation dependence
    - Problems at shared vertices
    - Unrepresentative vertex normals
- Reference
    - https://dawnarc.com/2018/06/shadingflatgouraudphong-shading%E7%9A%84%E5%B7%AE%E5%88%A5/
    - https://computergraphics.stackexchange.com/questions/377/shading-phong-vs-gouraud-vs-flat

----

## Clipping

### 2D Clipping - Segments
- Cohen-Sutherland Algorithm (outcodes)
    - idea: outcode (2*d bits)
        - 00 => in, 01/10 for different directions
    - use substraction to exlude a lot of multiplicatoin

### 2D Clipping - Polygons
- First deduce to clipping convex polygons by tessellation
- Sutherland-Hodgman algorithm
    - idea: 4 sides (top, down, right, left) oracles
    - used in SGI (some delay(?))

### 3D Clipping - Segments
- Cohen-Sutherland Method in 3D
    - 6 bit outcodes
    - If outcode(A)==outcode(B)==0
        - accept
    - If(outcode(A) and outcode(B))!=0
        - reject
    - Otherwise
        - Calculate an intersection 
        - recalculate outcode

### 3D Clipping - Polygon
- similar to 2d
- clipping box and check each side

### Alternative for Polygon
- Bounding Boxes for Items
    - easy to check if inside or need detailed clipping


----

## GPU and Shaders (End of Midterm)

### History
- only after Rasterization and Interpolation (including)
- all
- + Programmable Vertex Shaders and Programmable Fragment Processor
![](https://i.imgur.com/IF3eoSL.png =40%x)

### Software Support for Programmable Components
- Direct X 8 , 9, 10, 11, 12, …
- OpenGL Shading Language (GLSL)
- Metal Shading Language (by Apple) 
- ...
- Usage
    - write in other code and link is more common

### Essential GLSL pipeline
![](https://i.imgur.com/mR87jqs.png =40%x)


### Vertex Shaders
- Per-vertex 
    - Without knowledge about other vertices (parallelism)
- responsible for
    - Vertex transformation
    - Normal transformation
    - (Per-Vertex) Lighting
    - Color material application and color clamping
    - Texture coordinate generation
- Applications
    - movement in fields
        - v, t, g
    - Moving vertices
        - morphing/wave
    - Lighting
        - more realistics models

### Fragment Shaders
- "fragment" is potential pixel
- per-pixel calculations (parallelism)
- for
    - Operations on interpolated values
    - Texture access and application
    - Other functions: fog, color lookup, etc.
- Apps
    - Per-vertex lighting v.s. Per-fragment lighting
    - smooth shading v.s. bump mapping

### Geometry shader
- per primitives
- + Stream-output stage for IO of this stage result

### Whole Pipeline
![](https://i.imgur.com/dTMrk9n.png =40%x)
Note:
D3D11 improves the tessellation ability by three new
stages: hull shader, tessellator, domain shader.

(mid)

---
