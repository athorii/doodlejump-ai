#ifndef GEN_MANAGER_HPP_INCLUDE
#define GEN_MANAGER_HPP_INCLUDE

#include <fstream>
#include <unordered_map>
#include <vector>

#include "../game_object.hpp"

class Window;

class GenManager{
    public:
        GenManager() = default;

        void readGeneratedEntities(int numOfEntities, int score);


        struct Entity {
            Entity(int x_, int y_, GameObject::CollisionType type_);
    
            int x, y;
            GameObject::CollisionType type;
        };

        struct SubSeq {
            SubSeq(const std::vector<GenManager::Entity>& entities, int totalHeight);

            std::vector<GenManager::Entity> entities;
            int totalHeight; // Nouvelle variable pour stocker la hauteur totale
            std::vector<GameObject*> toObject() const;
        };
        std::vector<GenManager::Entity> generateEntities(int numOfEntities, int maxX, int maxY, int doodleJumpHeight, int score);

        std::vector<SubSeq> subSeqs;


    private:
        const std::unordered_map<std::string, GameObject::CollisionType> typeMap_{
            {"platform", GameObject::CollisionType::pNormal},
            {"mplatform", GameObject::CollisionType::pMovable},
            {"bplatform", GameObject::CollisionType::pBreakable},
            {"spring", GameObject::CollisionType::spring},
            {"enemy", GameObject::CollisionType::enemyNormal},
        };
};

#endif // SEQUENCE_MANAGER_HPP_INCLUDE
