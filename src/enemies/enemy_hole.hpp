#ifndef ENEMY_HOLE_HPP_INCLUDE
#define ENEMY_HOLE_HPP_INCLUDE

#include "enemy.hpp"

class EnemyHole : public Enemy {
public:
    using Enemy::Enemy;

    void update(unsigned deltaTime, Window* win) override;
    void draw(Window* win, const PointF& offset = {0, 0}) const override;
    CollisionType collide(GameObject* col, Window* win) override;

private:
    static CollisionType collideType_;

    enum class State {
        base,
        dying,
        vanished
    } state_ = State::base;

    int dieAnimationTimer_ = 0;
    int hoverTimer_ = 250;

    enum mDirection {
        right = 1,
        left = -1
    } direction_ = mDirection::right;

    float vx_=0.05f;
};

#endif //ENEMY_HOLE_HPP_INCLUDE