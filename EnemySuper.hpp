#ifndef ENEMYSUPER_HPP
#define ENEMYSUPER_HPP
#include <vector>

#include "Enemy.hpp"

class EnemySuper : public Enemy {
    static const float ExplosionRadius;
    float BossStage;
    std::vector<int> attackCnt;

   public:
    EnemySuper(int x, int y);
    void Update(float deltaTime) override;
    void CreateBullet() override {}
};
#endif  // ENEMYSUPER_HPP
