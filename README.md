# ZPG
This project is a semester work for the course Computer Graphics 
at the Faculty of Computer Science at VSB - Technical University of Ostrava. 
The goal of the project is to create a simple 3D scene using OpenGL and GLSL.

Built using CMake on Debian 12 bookworm (stable).

## Current state
- [x] Basic scene with sphere and two adjacent squares


- **WASD** for translation
- **E/F** for rotation along X
- **R/G** for rotation along Y
- **T/H** for rotation along Z
- **Z/X** for scaling

## TODO's
- Observer on transformations is currently global. e.g. no subject->notify implemented yet
- and more _in-code TODO's_

## Dependencies
- [libglfw3](https://www.glfw.org/) - *version 3.3.8*
- [libglfw3-dev](https://www.glfw.org/) - *version 3.3.8-1*
- libgl1-mesa-dev - *v22.3.6-1+deb12u1*
- libglew-dev - *2.2.0-4+b1*
- glew-utils - *2.2.0-4+b1*
