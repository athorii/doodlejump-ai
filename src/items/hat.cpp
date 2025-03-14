#include "hat.hpp"

#include "../RSDL/rsdl.hpp"
#include "../consts.hpp"

GameObject::CollisionType Hat::collideType_ = GameObject::CollisionType::hat;

void Hat::update(unsigned deltaTime, Window* win) {}

void Hat::draw(Window* win, const PointF& offset) const {
    win->draw_img(sprite::GAMETILES_FILE,
                  Rectangle(box_.x + offset.x, box_.y + offset.y, box_.w, box_.h),
                  sprite::item[currSprite_]);
}

GameObject::CollisionType Hat::collide(GameObject* col, Window* win) {
    if (state_ == State::base) {
        if (col != nullptr) {
            state_ = State::flying;
            currSprite_ = sprite::Item::FLYING_HAT;
            box_.y -= sprite::item[sprite::Item::FLYING_HAT].h - sprite::item[sprite::Item::FLYING_HAT].h;
            box_.w = sprite::item[currSprite_].w;
            box_.h = sprite::item[currSprite_].h;
            win->play_sound_effect(consts::SPRING_JUMP_SOUND);
        }
        return collideType_;
    }
    else return CollisionType::none;
}