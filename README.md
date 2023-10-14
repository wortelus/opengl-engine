# ZPG
This project is a semester work for the course Computer Graphics 
at the Faculty of Computer Science at VSB - Technical University of Ostrava. 
The goal of the project is to create a simple 3D scene using OpenGL and GLSL.

Built using CMake on Debian 12 bookworm (stable).

## Current state
- [x] Basic scene with sphere and monkey named Suzanne
- [x] Camera
- [x] Global transformations
- [x] WASD Movement + jumping

## Controls
### Camera
- **W/A/S/D** for movement
- **Space** for jumping

### Global transformations
- **arrows** for translation
- **E/F** for rotation along X
- **R/G** for rotation along Y
- **T/H** for rotation along Z
- **Z/X** for scaling

## TODO's
- Observer on transformations is currently not used. 
We call globally directly in scene all transformation operations (*no notify*).
- Observer on camera is not used, but implemented. We have no idea what purpose it should serve.
- and more _in-code TODO's_

## Dependencies
- [libglfw3](https://www.glfw.org/) - *version 3.3.8*
- [libglfw3-dev](https://www.glfw.org/) - *version 3.3.8-1*
- libgl1-mesa-dev - *v22.3.6-1+deb12u1*
- libglew-dev - *2.2.0-4+b1*
- glew-utils - *2.2.0-4+b1*

## Contact
Daniel Slavík

www.wortelus.eu
