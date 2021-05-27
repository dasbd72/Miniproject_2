#ifndef SOFAENEMY_HPP
#define SOFAENEMY_HPP
#include "Enemy.hpp"

class EnemySofa : public Enemy {
   public:
    EnemySofa(int x, int y);
    void Update(float deltaTime) override;
};
#endif  // SOFAENEMY_HPP
