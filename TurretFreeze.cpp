#include "TurretFreeze.hpp"

#include <allegro5/base.h>

#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "BulletIceCream.hpp"
#include "Enemy.hpp"
#include "Group.hpp"
#include "Point.hpp"
#include "ScenePlay.hpp"
#include "Turret.hpp"
const int TurretFreeze::Price = 40;
TurretFreeze::TurretFreeze(float x, float y) : Turret("play/turret-1.png", x, y, 30, 100, Price, 2.5) {
}
void TurretFreeze::CreateBullet() {
    Engine::Point diff = Engine::Point(1, 0);
    float rotation = ALLEGRO_PI / 2;
    getPlayScene()->BulletGroup->AddNewObject(new BulletIceCream(Position, diff, rotation, this));
    AudioHelper::PlayAudio("gun.wav");
}
