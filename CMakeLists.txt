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
        src/core/scene_loader.h src/core/scene_loader.cpp
        src/util/const.h
        src/util/event_args.h
        src/util/observer.h src/util/observer.cpp
        # models
        src/models/material.h
        src/models/drawable.h src/models/drawable.cpp
        src/models/model.h src/models/model.cpp
        # models animations
        src/models/animations/animation.h
        src/models/animations/centric_model.h src/models/animations/centric_model.cpp
        # shaders
        src/rendering/shaders/shader_loader.h src/rendering/shaders/shader_loader.cpp
        src/rendering/shaders/shader_uniforms.h src/rendering/shaders/shader_uniforms.cpp
        src/rendering/shaders/shader.h src/rendering/shaders/shader.cpp
        # camera
        src/rendering/camera.h src/rendering/camera.cpp
        # light
        src/rendering/light/light.h src/rendering/light/light.cpp
        # managers
        src/rendering/light_manager.h src/rendering/light_manager.cpp
        src/rendering/object_manager.h src/rendering/object_manager.cpp
        src/rendering/animation_manager.h src/rendering/animation_manager.cpp
        # transformations
        src/transform/transform.h src/transform/transform.cpp
        src/transform/transform_composite.h src/transform/transform_composite.cpp
        )

target_link_libraries(zpg ${OPENGL_LIBRARIES} glfw glm::glm GLEW::GLEW)