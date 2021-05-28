#include "EnemyNerd.hpp"

#include <string>

#include "AudioHelper.hpp"
#include "EBullet.hpp"
#include "ScenePlay.hpp"

EnemyNerd::EnemyNerd(int x, int y) : Enemy("play/enemy-4.png", x, y, 30, 30, 150, 75, 10, 170, 7) {
}
void EnemyNerd::Update(float deltaTime) {
    Enemy::Update(deltaTime);
}
void EnemyNerd::CreateBullet() {
    Engine::Point diff = Engine::Point(-1, 0);
    float rotation = ALLEGRO_PI / 2;
    getPlayScene()->BulletGroup->AddNewObject(new EBullet(Position, diff, rotation, this, 50));
    AudioHelper::PlayAudio("gun.wav");
}