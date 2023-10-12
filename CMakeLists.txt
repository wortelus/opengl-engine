cmake_minimum_required(VERSION 3.25)
project(zpg)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
add_subdirectory(libs/glm)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})

link_libraries(${GLEW_LIBRARIES})

add_executable(zpg src/main.cpp
        src/application.h src/application.cpp
        src/const.h
        src/event_args.h
        src/observer.h
        src/model.h src/model.cpp
        src/shader_loader.h src/shader_loader.cpp
        src/shader.h src/shader.cpp
        src/drawable.h src/drawable.cpp
        src/transform.h src/transform.cpp
        src/transform_composite.h src/transform_composite.cpp
        src/scene.h src/scene.cpp
        src/camera.h src/camera.cpp)

target_link_libraries(zpg ${OPENGL_LIBRARIES} glfw glm::glm GLEW::GLEW)