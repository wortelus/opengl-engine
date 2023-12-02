// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  29/9/2023

#ifndef ZPG_SHADER_LOADER_H
#define ZPG_SHADER_LOADER_H

//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

//Include GLM
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include "shader.h"
#include "../util/const.h"


class ShaderLoader {
private:
    SHADER_ALIAS_DATATYPE active_shader = SHADER_UNLOADED;
    std::vector<std::unique_ptr<Shader>> shaders;

    static std::string loadShaderFromFile(const std::string& path);
public:
    void loadShaders();
    Shader* loadShader(const SHADER_ALIAS_DATATYPE& alias);
    SHADER_ALIAS_DATATYPE getShaderAlias(const std::string& name);

    bool unloadShader();

    //
    // Iterator and ConstIterator definitions below
    //

    //
    // Iterator definitions
    //
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = typename std::vector<std::unique_ptr<Shader>>::iterator::difference_type;
        using value_type = Shader;
        using pointer = Shader*;

        explicit Iterator(typename std::vector<std::unique_ptr<Shader>>::iterator it)
                : it(it) {}

        Iterator& operator++() {
            ++it;
            return *this;
        }

        Shader* operator*() {
            return it->get();
        }

        bool operator!=(const Iterator& other) const {
            return it != other.it;
        }

    public:
        typename std::vector<std::unique_ptr<Shader>>::iterator it;
    };

    //
    // ConstIterator definitions
    //
    class ConstIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = typename std::vector<std::unique_ptr<Shader>>::const_iterator::difference_type;
        using value_type = const Shader;
        using pointer = const Shader*;

        explicit ConstIterator(typename std::vector<std::unique_ptr<Shader>>::const_iterator it)
                : it(it) {}

        ConstIterator& operator++() {
            ++it;
            return *this;
        }

        const Shader* operator*() const {
            return it->get();
        }

        bool operator!=(const ConstIterator& other) const {
            return it != other.it;
        }

    private:
        typename std::vector<std::unique_ptr<Shader>>::const_iterator it;
    };

    //
    // Iterator and ConstIterator getters
    //
public:
    Iterator begin() {
        return Iterator(shaders.begin());
    }

    Iterator end() {
        return Iterator(shaders.end());
    }

    [[nodiscard]] ConstIterator cbegin() const {
        return ConstIterator(shaders.cbegin());
    }

    [[nodiscard]] ConstIterator cend() const {
        return ConstIterator(shaders.cend());
    }

    [[nodiscard]] ConstIterator begin() const {
        return ConstIterator(shaders.cbegin());
    }

    [[nodiscard]] ConstIterator end() const {
        return ConstIterator(shaders.cend());
    }
};


#endif //ZPG_SHADER_LOADER_H
