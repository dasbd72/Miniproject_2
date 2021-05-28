#include "EnemySofa.hpp"

#include <string>

#include "AudioHelper.hpp"
#include "EBullet.hpp"
#include "ScenePlay.hpp"

EnemySofa::EnemySofa(int x, int y) : Enemy("play/enemy-2.png", x, y, 16, 100, 10, 10, 10, 100, 3) {
    // Use bounding circle to detect collision is for simplicity, pixel-perfect collision can be implemented quite easily,
    // and efficiently if we use AABB collision detection first, and then pixel-perfect collision.
}
void EnemySofa::Update(float deltaTime) {
    Enemy::Update(deltaTime);
}
void EnemySofa::CreateBullet() {
    Engine::Point diff = Engine::Point(-1, 0);
    float rotation = ALLEGRO_PI / 2;
    getPlayScene()->BulletGroup->AddNewObject(new EBullet(Position, diff, rotation, this, 10));
    AudioHelper::PlayAudio("gun.wav");
}