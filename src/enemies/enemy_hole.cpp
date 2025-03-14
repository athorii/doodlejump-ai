#include "enemy_hole.hpp"

#include "../RSDL/rsdl.hpp"
#include "../spritesheet.hpp"

GameObject::CollisionType EnemyHole::collideType_ = GameObject::CollisionType::enemyHole;

void EnemyHole::update(unsigned deltaTime, Window* win) {
    if (state_ == State::base) {
        
    }
    else if (state_ == State::dying) {
        if (dieAnimationTimer_ > 400) state_ = State::vanished;
        dieAnimationTimer_ += deltaTime;
        box_.y += 0.2 * deltaTime;
    }
}

void EnemyHole::draw(Window* win, const PointF& offset) const {
    if (state_ != State::vanished) {
        win->draw_img(sprite::GAMETILES_FILE,
                      Rectangle(box_.x + offset.x, box_.y + offset.y, box_.w, box_.h),
                      sprite::enemy[sprite::Enemy::HOLE]);
    }
}

GameObject::CollisionType EnemyHole::collide(GameObject* col, Window* win) {
    if (state_ == State::base) {
        if (col != nullptr) {
            state_ = State::dying;
        }
        return collideType_;
    }
    else return CollisionType::none;
}