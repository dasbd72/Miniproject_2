#include "EnemyStrong.hpp"

#include <string>

EnemyStrong::EnemyStrong(int x, int y) : Enemy("play/enemy-3.png", x, y, 20, 20, 100, 50, 10, 30) {
    // Use bounding circle to detect collision is for simplicity, pixel-perfect collision can be implemented quite easily,
    // and efficiently if we use AABB collision detection first, and then pixel-perfect collision.
}
void EnemyStrong::Update(float deltaTime) {
    Enemy::Update(deltaTime);
}
