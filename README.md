# ZPG
In the days of academic endeavors, a project was conceived under the 
esteemed halls of the Faculty of Computer Science at VSB - 
Technical University of Ostrava. This undertaking was a 
testament for the course **Principles of Computer Graphics**.

"Let there be a 3D realm," it was decreed, and thus, using the sacred 
tools of OpenGL and GLSL, a scene was birthed.

Crafted upon the foundation of Debian 12 bookworm, the steadfast and 
unyielding, using the scriptures of CMake.

## Current state
- [x] Basic scene with 4 spheres
- [x] Camera
- [x] Global transformations
- [x] WASD Movement + jumping
- [x] Lighting, ambient, diffuse, specular point lights
- [x] Dynamic shader loading
- [x] Materials
- [x] Global illumination, constant, Phong, Blinn-Phong point lights
- [x] Multiple scenes

## Controls
### Camera
- Wander with W/A/S/D.
- Jump using Space key.

### Global transformations
- **arrows** to translate
- **E/F** for spin along the X-axis
- **R/G** for rotation along the Y-axis
- **T/H** for rotation along the Z-axis
- **Z/X** for scaling

### Scene selection
- using `current_scene_id` *(0-2)* in application.h, dynamic scene loading is in the works

## TODO's - Tablets of Future Endeavors
- Observer on transformations is currently not used. 
We call globally directly in scene all transformation operations (*no notify*).
- Observer on camera is not used, but implemented.
- We have kinda optimized the MVP matrix calculation, 
but it could be maybe better to pass it as a whole to the shader.
- Maybe better scene loading, the way we make it now breaks encapsulation.
- Review light intensity in lambert shader, it lit up the whole object, while blinn and phong didn't.
- Reduce implementation dependencies by applying the observer pattern.
- and more _in-code TODO's_

## Dependencies
- [libglfw3](https://www.glfw.org/) - *version 3.3.8*
- [libglfw3-dev](https://www.glfw.org/) - *version 3.3.8-1*
- libgl1-mesa-dev - *v22.3.6-1+deb12u1*
- libglew-dev - *2.2.0-4+b1*
- glew-utils - *2.2.0-4+b1*

## Seek the Scribe
Daniel Slavík, keeper of the chronicles.

[The digital temple - wortelus.eu](https://www.wortelus.eu) 
