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

## Sacred Scripts of Luminescence
- **Constant**: The foundational beacon, it emanates unwavering light, 
gracing every form with steadfast illumination.
- **Lambert**: Echoing the wisdom of yore, it scatters diffuse 
reflections with equanimity, painting every crevice and crest with its gentle touch.
- **Phong**: Renowned as the luminary elite, it ushers in a dance of specular 
reflections, lending a glint reminiscent of stars. 
- **Blinn-Phong**: An evolved descendant of Phong, it merges 
the essence of view and light, casting reflections that dazzle 
with a sophistication only matched by its predecessors.

## Building the Shrine
1. **Invoking the Oracle, `CMake`**

With reverence and a dash of bravado, navigate thy terminal to 
the root temple (directory) of "zpg". Then chant the incantation:

```shell
mkdir build
cd build
cmake ..
```
2. **Summoning the Constructor, `Make`**

With the prophecies of CMake now revealed, call forth the ancient builder:
```shell
make
```

Behold, as "Make", the grand architect, brings "zpg" to life, forging 
executables from the ethereal realm of source code.

3. **Rejoice and Run**

With the rites completed, the executable artifact is now amongst us. 
Run it, and bask in the glory of your creation. For it is the digital alchemy, 
turning lines of text into a mosaic of pixels and logic, painting stories in real-time.
## Controls
### Camera
- Wander with W/A/S/D.
- Ascend with the gift of Space.

### Global transformations
- **arrows** to translate
- **E/F** for spin along the X-axis
- **R/G** for rotation along the Y-axis
- **T/H** for rotation along the Z-axis
- **Z/X** for scaling

### Scene selection
- **F2** for the next scene

## Tablets of Future Endeavors
- Observer on transformations is currently not used.
We call globally directly in scene all transformation operations (*no notify*).
- and more _in-code TODO's_

## The Sacred Relics
- [libglfw3](https://www.glfw.org/) - *version 3.3.8*
- [libglfw3-dev](https://www.glfw.org/) - *version 3.3.8-1*
- [libgl1-mesa-dev](https://www.mesa3d.org/) - *v22.3.6-1+deb12u1*
- [libglew-dev](https://glew.sourceforge.net/) - *2.2.0-4+b1*
- [glew-utils](https://glew.sourceforge.net/) - *2.2.0-4+b1*

## Seek the Scribe
Daniel Slavík, _known in revered circles as wortelus_, keeper of the chronicles.

[The digital temple - wortelus.eu](https://www.wortelus.eu) 
