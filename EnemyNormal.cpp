#include "EnemyNormal.hpp"

#include <string>

#include "AudioHelper.hpp"
#include "EBullet.hpp"
#include "ScenePlay.hpp"

EnemyNormal::EnemyNormal(int x, int y) : Enemy("play/enemy-1.png", x, y, 10, 50, 5, 5, 5, 150, 5) {
    // nTODO 2 (6/8): You can imitate the 2 files: 'EnemyNormal.hpp', 'EnemyNormal.cpp' to create a new enemy.
}
void EnemyNormal::Update(float deltaTime) {
    Enemy::Update(deltaTime);
}
void EnemyNormal::CreateBullet() {
    Engine::Point diff = Engine::Point(-1, 0);
    float rotation = ALLEGRO_PI / 2;
    getPlayScene()->BulletGroup->AddNewObject(new EBullet(Position, diff, rotation, this, 5));
    AudioHelper::PlayAudio("gun.wav");
}