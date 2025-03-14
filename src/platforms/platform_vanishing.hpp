#ifndef PLATFORM_VANISHING_HPP_INCLUDE
#define PLATFORM_VANISHING_HPP_INCLUDE

#include "../spritesheet.hpp"
#include "platform.hpp"

class PlatformVanishing : public Platform {
public:
    using Platform::Platform;

    void update(unsigned deltaTime, Window* win) override;
    void draw(Window* win, const PointF& offset = {0, 0}) const override;
    CollisionType collide(GameObject* col, Window* win) override;

private:
    static CollisionType collideType_;

    enum class State {
        base,
        vanishing,
        vanished
    } state_ = State::base;

    int disapearAnimationTimer = 0;
    sprite::Platform currSprite_ = sprite::Platform::VANISHING;
};

#endif //PLATFORM_VANISHING_HPP_INCLUDE