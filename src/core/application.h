// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  29/9/2023


#ifndef ZPG_APPLICATION_H
#define ZPG_APPLICATION_H

//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

#include <utility>
#include <vector>
#include <string>

#include "scene.h"
#include "loaders/scene_loader.h"
#include "../shaders/shader_loader.h"
#include "../models/drawable.h"

class Application {
private:
    GLFWwindow* window;
    std::shared_ptr<ShaderLoader> shader_loader;

    int current_scene_id = DEFAULT_SCENE;
    std::unique_ptr<Scene> scene;

    const char* title;
    float ratio;
    int width;
    int height;

    void nextScene();
    void update_scene_aspect(const int& new_width, const int& new_height);
public:
    Application(int width, int height, const char* title);
    ~Application();

    void init();
    static void info();
    void run();

    void handleKeyEvent(int key, int scancode, int action, int mods);
    void handleCursorEvent(double x_pos, double y_pos);
    void handleMouseButtonEvent(int button, int action, int mode);
    static void errorCallback(int error, const char* description);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void windowCloseCallback(GLFWwindow* window);
    static void windowFocusCallback(GLFWwindow* window, int focused);
    static void windowIconifyCallback(GLFWwindow* window, int iconified);
    static void windowSizeCallback(GLFWwindow* window, int width, int height);
    static void cursorCallback(GLFWwindow* window, double x, double y);
    static void buttonCallback(GLFWwindow* window, int button, int action, int mode);
};


#endif //ZPG_APPLICATION_H
