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
        src/core/application.h src/core/application.cpp
        src/core/scene.h src/core/scene.cpp
        src/util/const.h
        src/util/event_args.h
        src/util/observer.h
        src/models/material.h
        src/models/drawable.h src/models/drawable.cpp
        src/models/model.h src/models/model.cpp
        src/rendering/shader_loader.h src/rendering/shader_loader.cpp
        src/rendering/shader.h src/rendering/shader.cpp
        src/rendering/camera.h src/rendering/camera.cpp
        src/rendering/light/light.h src/rendering/light/light.cpp
        src/transform/transform.h src/transform/transform.cpp
        src/transform/transform_composite.h src/transform/transform_composite.cpp
        src/rendering/light_manager.h src/rendering/light_manager.cpp
        src/core/scene_loader.h src/core/scene_loader.cpp)

target_link_libraries(zpg ${OPENGL_LIBRARIES} glfw glm::glm GLEW::GLEW)