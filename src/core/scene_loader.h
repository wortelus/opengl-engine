// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  22/10/2023

#ifndef ZPG_SCENE_LOADER_H
#define ZPG_SCENE_LOADER_H


#include "scene.h"

class SceneLoader {
public:
    SceneLoader() = delete;
    SceneLoader(SceneLoader const&) = delete;
    void operator=(SceneLoader const&) = delete;
    ~SceneLoader() = delete;

    static std::unique_ptr<Scene>
    loadScene(int* scene_id, GLFWwindow& window_reference, const int& initial_width, const int& initial_height);

private:
    static std::unique_ptr<Scene>
    loadSceneA(GLFWwindow& window_reference, const int& initial_width, const int& initial_height);
    static std::unique_ptr<Scene>
    loadSceneB(GLFWwindow& window_reference, const int& initial_width, const int& initial_height);
    static std::unique_ptr<Scene>
    loadSceneC(GLFWwindow& window_reference, const int& initial_width, const int& initial_height);
};

#endif //ZPG_SCENE_LOADER_H
