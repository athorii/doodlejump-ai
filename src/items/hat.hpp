#ifndef HAT_NORMAL_HPP_INCLUDE
#define HAT_NORMAL_HPP_INCLUDE

#include "../spritesheet.hpp"
#include "item.hpp"

class Window;

class Hat : public Item {
public:
    using Item::Item;

    void update(unsigned deltaTime, Window* win) override;
    void draw(Window* win, const PointF& offset = {0, 0}) const override;
    CollisionType collide(GameObject* col, Window* win) override;

private:
    static CollisionType collideType_;

    enum class State {
        base,
        flying
    } state_ = State::base;
    sprite::Item currSprite_ = sprite::Item::HAT;
};

#endif //SPRING_NORMAL_HPP_INCLUDE