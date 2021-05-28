#ifndef ENEMYNERD_HPP
#define ENEMYNERD_HPP
#include "Enemy.hpp"

class EnemyNerd : public Enemy {
   public:
    EnemyNerd(int x, int y);
    void Update(float deltaTime) override;
    void CreateBullet() override;
};
#endif  // ENEMYNERD_HPP
