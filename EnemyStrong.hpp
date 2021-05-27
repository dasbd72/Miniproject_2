#ifndef STRONGENEMY_HPP
#define STRONGENEMY_HPP
#include "Enemy.hpp"

class EnemyStrong : public Enemy {
   public:
    EnemyStrong(int x, int y);
    void Update(float deltaTime) override;
};
#endif  // STRONGENEMY_HPP
