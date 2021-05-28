#ifndef NORMALENEMY_HPP
#define NORMALENEMY_HPP
#include "Enemy.hpp"

class EnemyNormal : public Enemy {
   public:
    EnemyNormal(int x, int y);
    void Update(float deltaTime) override;
    void CreateBullet() override;
};
#endif  // NORMALENEMY_HPP
