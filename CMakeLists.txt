cmake_minimum_required(VERSION 3.25)
project(zpg)

set(CMAKE_CXX_STANDARD 17)

find_library(SOIL_LIBRARY NAMES SOIL PATHS /usr/lib)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(assimp REQUIRED)
add_subdirectory(libs/glm)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})

link_libraries(${GLEW_LIBRARIES})

add_executable(zpg src/main.cpp
        # core functionalities
        src/core/application.h src/core/application.cpp
        src/core/scene.h src/core/scene.cpp
        # loaders
        src/core/loaders/scene_loader.h src/core/loaders/scene_loader.cpp
        src/core/loaders/model_loader.h src/core/loaders/model_loader.cpp
        src/core/loaders/texture_loader.h src/core/loaders/texture_loader.cpp
        src/core/loaders/asset_loader.h src/core/loaders/asset_loader.cpp
        # utilities and constants
        src/util/const.h
        src/util/const_lights.h
        src/util/event_args.h
        src/util/observer.h src/util/observer.cpp
        # models
        src/models/drawable.h src/models/drawable.cpp
        src/models/model.h src/models/model.cpp
        # model properties
        src/models/properties/material.h
        src/models/properties/texture.h src/models/properties/texture.cpp
        # models animations
        src/models/animations/animation.h
        src/models/animations/centric_model.h src/models/animations/centric_model.cpp
        src/models/animations/cubic_bezier.h src/models/animations/cubic_bezier.cpp
        src/models/animations/cubic_chain.h src/models/animations/cubic_chain.cpp
        src/models/animations/linear.h src/models/animations/linear.cpp
        # shaders
        src/rendering/shaders/shader_loader.h src/rendering/shaders/shader_loader.cpp
        src/rendering/shaders/shader.h src/rendering/shaders/shader.cpp
        # camera
        src/rendering/camera.h src/rendering/camera.cpp
        # light
        src/rendering/light/light.h src/rendering/light/light.cpp
        src/rendering/light/point_light.h src/rendering/light/point_light.cpp
        src/rendering/light/directional_light.h src/rendering/light/directional_light.cpp
        src/rendering/light/spotlight.h src/rendering/light/spotlight.cpp
        # managers
        src/rendering/light_manager.h src/rendering/light_manager.cpp
        src/rendering/object_manager.h src/rendering/object_manager.cpp
        src/rendering/animation_manager.h src/rendering/animation_manager.cpp
        # transformations
        src/transform/transform.h src/transform/transform.cpp
        src/transform/transform_composite.h src/transform/transform_composite.cpp
        # shader uniforms
        src/rendering/shaders/uniforms/uniforms.h src/rendering/shaders/uniforms/uniforms.cpp
        src/rendering/shaders/uniforms/shader_uniforms.h src/rendering/shaders/uniforms/shader_uniforms.cpp
        src/rendering/shaders/uniforms/dynamic_uniforms.h src/rendering/shaders/uniforms/dynamic_uniforms.cpp
        )

target_link_libraries(zpg ${OPENGL_LIBRARIES} ${SOIL_LIBRARY} glfw glm::glm GLEW::GLEW assimp::assimp)