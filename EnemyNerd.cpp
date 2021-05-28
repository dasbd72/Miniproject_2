#include "EnemyNerd.hpp"

#include <string>

EnemyNerd::EnemyNerd(int x, int y) : Enemy("play/enemy-4.png", x, y, 30, 10, 150, 75, 10, 100) {
}
void EnemyNerd::Update(float deltaTime) {
    Enemy::Update(deltaTime);
}