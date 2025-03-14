#include "platform_vanishing.hpp"

#include "../RSDL/rsdl.hpp"
#include "../consts.hpp"

GameObject::CollisionType PlatformVanishing::collideType_ = GameObject::CollisionType::pVanishing;

void PlatformVanishing::update(unsigned deltaTime, Window* win) {
    if (state_ == State::vanishing) {
        disapearAnimationTimer += deltaTime;
        if (disapearAnimationTimer >= 650) {
            state_ = State::vanished;
        }
        else if (disapearAnimationTimer > 120) {
            currSprite_ = sprite::Platform::VANISHING_B3;
        }
        else if (disapearAnimationTimer > 80) {
            currSprite_ = sprite::Platform::VANISHING_B2;
        }
        else if (disapearAnimationTimer > 40) {
            currSprite_ = sprite::Platform::VANISHING_B1;
        }
        box_.w = sprite::platform[currSprite_].w;
        box_.h = sprite::platform[currSprite_].h;
        box_.y += 0.4 * deltaTime;
    }
}

void PlatformVanishing::draw(Window* win, const PointF& offset) const {
    if (state_ != State::vanished) {
        win->draw_img(sprite::GAMETILES_FILE,
                      Rectangle(box_.x + offset.x, box_.y + offset.y, box_.w, box_.h),
                      sprite::platform[currSprite_]);
    }
}

GameObject::CollisionType PlatformVanishing::collide(GameObject* col, Window* win) {
    if (state_ == State::base) {
        if (col != nullptr) {
            state_ = State::vanishing;
            win->play_sound_effect(consts::PLAT_BREAK_SOUND);
        }
        return collideType_;
    }
    else return CollisionType::none;
}