// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  29/10/2023

#ifndef ZPG_ANIMATION_MANAGER_H
#define ZPG_ANIMATION_MANAGER_H


#include <algorithm>
#include <functional>
#include <vector>
#include <memory>
#include "../models/animations/animation.h"

class AnimationManager {
private:
    std::vector<std::shared_ptr<Animation>> animations;
public:
    void addAnimation(const std::shared_ptr<Animation>& animation);
    void applyAnimations(const std::function<void(Animation*)>& func);

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
        using difference_type = typename std::vector<std::shared_ptr<Animation>>::iterator::difference_type;
        using value_type = Animation;
        using pointer = Animation*;

        explicit Iterator(typename std::vector<std::shared_ptr<Animation>>::iterator it)
                : it(it) {}

        Iterator& operator++() {
            ++it;
            return *this;
        }

        Animation* operator*() {
            return it->get();
        }

        bool operator!=(const Iterator& other) const {
            return it != other.it;
        }

    public:
        typename std::vector<std::shared_ptr<Animation>>::iterator it;
    };

    //
    // ConstIterator definitions
    //
    class ConstIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = typename std::vector<std::shared_ptr<Animation>>::const_iterator::difference_type;
        using value_type = const Animation;
        using pointer = const Animation*;

        explicit ConstIterator(typename std::vector<std::shared_ptr<Animation>>::const_iterator it)
                : it(it) {}

        ConstIterator& operator++() {
            ++it;
            return *this;
        }

        const Animation* operator*() const {
            return it->get();
        }

        bool operator!=(const ConstIterator& other) const {
            return it != other.it;
        }

    private:
        typename std::vector<std::shared_ptr<Animation>>::const_iterator it;
    };

    //
    // Iterator and ConstIterator getters
    //
public:
    Iterator begin() {
        return Iterator(animations.begin());
    }

    Iterator end() {
        return Iterator(animations.end());
    }

    [[nodiscard]] ConstIterator cbegin() const {
        return ConstIterator(animations.cbegin());
    }

    [[nodiscard]] ConstIterator cend() const {
        return ConstIterator(animations.cend());
    }

    [[nodiscard]] ConstIterator begin() const {
        return ConstIterator(animations.cbegin());
    }

    [[nodiscard]] ConstIterator end() const {
        return ConstIterator(animations.cend());
    }
};


#endif //ZPG_ANIMATION_MANAGER_H
