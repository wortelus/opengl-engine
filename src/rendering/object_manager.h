// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation: 22/10/2023

#ifndef ZPG_OBJECT_MANAGER_H
#define ZPG_OBJECT_MANAGER_H

#include "../models/drawable.h"
#include "../shaders/shader_loader.h"

class ObjectManager {
private:
    // skybox
    std::unique_ptr<DrawableObject> skybox;
    // objects currently participating in rendering pipeline
    std::vector<std::unique_ptr<DrawableObject>> objects;
    // not part of the scene yet
    std::vector<std::unique_ptr<DrawableObject>> queued_objects;
    // prepared to be deleted
    std::vector<char> inter_ids_to_delete;
    // next interaction id
    char next_interact_id = 1;
private:
    void enqueue(ShaderLoader* shader_loader);
    void sortObjects();
    void deleteObjects();
public:
    ~ObjectManager();

    DrawableObject& addObject(std::unique_ptr<DrawableObject> obj);

    DrawableObject& assignSkybox(std::unique_ptr<DrawableObject> obj);
    [[nodiscard]] bool hasSkybox() const { return skybox != nullptr; }
    [[nodiscard]] DrawableObject& getSkybox() const { return *skybox; }

    DrawableObject* getByInteractID(const char& id);
    void deleteByInteractID(const char& id);

    // enqueue and sort objects by shader alias
    void preprocess(ShaderLoader* shader_loader);

    // global objects components
    void translate(const glm::vec3& translation);

    // global objects rotations
    void rotate(const glm::vec3& axis_degrees);

    // global objects scaling
    void scale(const glm::vec3& scale);

    //
    // Iterator and ConstIterator definitions below
    //

    //
    // Iterator definitions
    //
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = typename std::vector<std::unique_ptr<DrawableObject>>::iterator::difference_type;
        using value_type = DrawableObject;
        using pointer = DrawableObject*;

        explicit Iterator(typename std::vector<std::unique_ptr<DrawableObject>>::iterator it)
                : it(it) {}

        Iterator& operator++() {
            ++it;
            return *this;
        }

        DrawableObject* operator*() {
            return it->get();
        }

        bool operator!=(const Iterator& other) const {
            return it != other.it;
        }

    public:
        typename std::vector<std::unique_ptr<DrawableObject>>::iterator it;
    };

    //
    // ConstIterator definitions
    //
    class ConstIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = typename std::vector<std::unique_ptr<DrawableObject>>::const_iterator::difference_type;
        using value_type = const DrawableObject;
        using pointer = const DrawableObject*;

        explicit ConstIterator(typename std::vector<std::unique_ptr<DrawableObject>>::const_iterator it)
                : it(it) {}

        ConstIterator& operator++() {
            ++it;
            return *this;
        }

        const DrawableObject* operator*() const {
            return it->get();
        }

        bool operator!=(const ConstIterator& other) const {
            return it != other.it;
        }

    private:
        typename std::vector<std::unique_ptr<DrawableObject>>::const_iterator it;
    };

    //
    // Iterator and ConstIterator getters
    //
public:
    Iterator begin() {
        return Iterator(objects.begin());
    }

    Iterator end() {
        return Iterator(objects.end());
    }

    [[nodiscard]] ConstIterator cbegin() const {
        return ConstIterator(objects.cbegin());
    }

    [[nodiscard]] ConstIterator cend() const {
        return ConstIterator(objects.cend());
    }

    [[nodiscard]] ConstIterator begin() const {
        return ConstIterator(objects.cbegin());
    }

    [[nodiscard]] ConstIterator end() const {
        return ConstIterator(objects.cend());
    }
};


#endif //ZPG_OBJECT_MANAGER_H
