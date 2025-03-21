#include "gen_manager.hpp"

#include <stdexcept>

#include "../consts.hpp"
#include "../enemies/enemy_normal.hpp"
#include "../items/spring.hpp"
#include "../platforms/platform_breakable.hpp"
#include "../platforms/platform_movable.hpp"
#include "../platforms/platform_normal.hpp"
#include "../spritesheet.hpp"
#include "../utils/point_f.hpp"
#include "../utils/rectangle_f.hpp"

#include <random>
#include <chrono>
#include <algorithm>

#define ENTITY_NUMBER 15


GenManager::Entity::Entity(int x_, int y_, GameObject::CollisionType type_)
    : x(x_),
      y(y_),
      type(type_) {}

GenManager::SubSeq::SubSeq(const std::vector<GenManager::Entity>& entities, int totalHeight)
    : entities(entities),
      totalHeight(totalHeight) {}


void GenManager::readGeneratedEntities(int numOfEntities,int score) {
    for (int i = 0; i < numOfEntities; i++) {
        auto entities = generateEntities(ENTITY_NUMBER, consts::WIN_WIDTH, consts::WIN_HEIGHT, 70, score);
        
        // Calcul de la hauteur totale de cette séquence
        int totalHeight = 0;
        for (const auto& entity : entities) {
            totalHeight = std::max(totalHeight, entity.y);
        }
        subSeqs.emplace_back(entities, totalHeight);
    }

}

std::vector<GenManager::Entity> GenManager::generateEntities(int numOfEntities, int maxX, int maxY, int doodleJumpHeight, int score) {
    std::vector<GenManager::Entity> entities;
    entities.reserve(numOfEntities);

    std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> xDist(0, maxX);
    std::uniform_int_distribution<int> yDist(0, doodleJumpHeight / 2);
    std::uniform_int_distribution<int> typeDist(0, 2);
    std::uniform_int_distribution<int> enemyChance(0, 1);

    int lastPlatformY = 0;
    int enemyCount = 0;
    int maxEnemies = (score >= 1000) ? 2 : 1;

    int minXSpacing = 40 + (score / 500) * 10;
    int maxPlatforms = numOfEntities ;//- (score / 3000);
    maxPlatforms = std::max(3, maxPlatforms);

    // Ensure at least one of each platform type
    std::vector<GameObject::CollisionType> requiredTypes = {
        GameObject::CollisionType::pNormal,
        GameObject::CollisionType::pMovable,
        //GameObject::CollisionType::pBreakable
    };

    for (int i = 0; i < maxPlatforms; i++) {
        int x = xDist(gen);
        if (i > 0) {
            x += std::uniform_int_distribution<int>(-minXSpacing / 2, minXSpacing / 2)(gen);
            x = std::clamp(x, 0, maxX);
        }

        int minYGap = doodleJumpHeight + (score / 100); // Minimum gap increases with score
        int maxYGap = doodleJumpHeight-20 + (score / 50);      // Maximum gap increases with score
        
        if (maxYGap - minYGap <= 1) {
            minYGap = maxYGap - 1; // Fixer minYGap à maxYGap - 1
        }
        
        int y = lastPlatformY + std::uniform_int_distribution<int>(minYGap, maxYGap)(gen);

        if (i > 0 && entities.back().type != GameObject::CollisionType::pBreakable) {
            if (y <= entities.back().y + doodleJumpHeight / 2) {
                y = entities.back().y + doodleJumpHeight / 2 + 1; // Ensure minimum gap is respected
            }
        }

        GameObject::CollisionType type;
        if (static_cast<size_t>(i) < requiredTypes.size()) {
            type = requiredTypes[i];
        } else {
            type = GameObject::CollisionType::pNormal;
            if (i > 0 && typeDist(gen) == 1) {
                type = GameObject::CollisionType::pMovable;
            } /*else if (i > 1 && typeDist(gen) == 2) {
                type = GameObject::CollisionType::pBreakable;
            }*/
        }

        entities.emplace_back(x, y, type);
        if (type != GameObject::CollisionType::pBreakable) {
            lastPlatformY = y;
        } else if (!entities.empty() && entities.back().type != GameObject::CollisionType::pBreakable) {
            // Si la plateforme actuelle est cassable, utilisez la dernière plateforme valide
            lastPlatformY = entities.back().y;
        }
    }

    //WIP

    for (size_t i = 0; i < entities.size(); i++) {
        /*if (enemyCount <= maxEnemies && enemyChance(gen) == 1 && score >= 1000) {
            int enemyX = std::clamp(entities[i].x + std::uniform_int_distribution<int>(-50, 50)(gen), 0, maxX);
            int enemyY = entities[i].y - doodleJumpHeight / 4;
            entities.emplace_back(enemyX, enemyY, GameObject::CollisionType::enemyNormal);
            enemyCount++;
            printf("enemy at %d %d\n", enemyX, enemyY);
        }
        
        if (i > 0 && (entities[i].y - entities[i - 1].y > doodleJumpHeight / 2)) {
            int springX = entities[i - 1].x;
            int springY = entities[i - 1].y + 20;
            if (entities[i - 1].type == GameObject::CollisionType::pNormal) {
                entities.emplace_back(springX, springY, GameObject::CollisionType::spring);
            }
        }*/
    }
    

    return entities;
}


static PointF getTopLeftFromBottomMiddle(int x, int y, int w, int h) {
    return PointF(x - w / 2, consts::WIN_HEIGHT - (y + h));
}

std::vector<GameObject*> GenManager::SubSeq::toObject() const {
    std::vector<GameObject*> seqObjs;
    seqObjs.reserve(entities.size());

    for (auto& e : entities) {
        switch (e.type) {
            int width;
            int height;
        case GameObject::CollisionType::pNormal:
            width = sprite::platform[sprite::Platform::NORMAL].w;
            height = sprite::platform[sprite::Platform::NORMAL].h;
            seqObjs.push_back(new PlatformNormal(RectangleF(getTopLeftFromBottomMiddle(e.x, e.y, width, height), width, height)));
            break;
        case GameObject::CollisionType::pMovable:
            width = sprite::platform[sprite::Platform::MOVABLE].w;
            height = sprite::platform[sprite::Platform::MOVABLE].h;
            seqObjs.push_back(new PlatformMovable(RectangleF(getTopLeftFromBottomMiddle(e.x, e.y, width, height), width, height)));
            break;
        case GameObject::CollisionType::pBreakable:
            width = sprite::platform[sprite::Platform::BREAKABLE].w;
            height = sprite::platform[sprite::Platform::BREAKABLE].h;
            seqObjs.push_back(new PlatformBreakable(RectangleF(getTopLeftFromBottomMiddle(e.x, e.y, width, height), width, height)));
            break;
        case GameObject::CollisionType::spring:
            width = sprite::item[sprite::Item::SPRING].w;
            height = sprite::item[sprite::Item::SPRING].h;
            seqObjs.push_back(new Spring(RectangleF(getTopLeftFromBottomMiddle(e.x, e.y, width, height), width, height)));
            break;
        case GameObject::CollisionType::enemyNormal:
            width = sprite::enemy[sprite::Enemy::NORM].w;
            height = sprite::enemy[sprite::Enemy::NORM].h;
            seqObjs.push_back(new EnemyNormal(RectangleF(getTopLeftFromBottomMiddle(e.x, e.y, width, height), width, height),
                                              RectangleF(10, 10, width - 20, height - 20)));
            break;
        default: break;
        }
    }

    return seqObjs;
}