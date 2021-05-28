#include "EnemyNormal.hpp"

#include <string>

EnemyNormal::EnemyNormal(int x, int y) : Enemy("play/enemy-1.png", x, y, 10, 50, 5, 5, 5, 50) {
    // nTODO 2 (6/8): You can imitate the 2 files: 'EnemyNormal.hpp', 'EnemyNormal.cpp' to create a new enemy.
}
void EnemyNormal::Update(float deltaTime) {
    Enemy::Update(deltaTime);
}