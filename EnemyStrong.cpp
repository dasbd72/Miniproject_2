#include "EnemyStrong.hpp"

#include <string>

#include "AudioHelper.hpp"
#include "EBullet.hpp"
#include "ScenePlay.hpp"

EnemyStrong::EnemyStrong(int x, int y) : Enemy("play/enemy-3.png", x, y, 20, 20, 100, 50, 10, 110, 5) {
    // Use bounding circle to detect collision is for simplicity, pixel-perfect collision can be implemented quite easily,
    // and efficiently if we use AABB collision detection first, and then pixel-perfect collision.
}
void EnemyStrong::Update(float deltaTime) {
    Enemy::Update(deltaTime);
}
void EnemyStrong::CreateBullet() {
    Engine::Point diff = Engine::Point(-1, 0);
    float rotation = ALLEGRO_PI / 2;
    getPlayScene()->BulletGroup->AddNewObject(new EBullet(Position, diff, rotation, this, 20));
    AudioHelper::PlayAudio("gun.wav");
}