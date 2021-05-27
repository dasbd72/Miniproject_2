#include "EnemyNerd.hpp"

#include <string>

EnemyNerd::EnemyNerd(int x, int y) : Enemy("play/enemy-4.png", x, y, 30, 10, 150, 75, 10, 30) {
}
void EnemyNerd::Update(float deltaTime) {
    Enemy::Update(deltaTime);
}