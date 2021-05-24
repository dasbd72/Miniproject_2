#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "BulletFire.hpp"
#include "Group.hpp"
#include "TurretFire.hpp"
#include "ScenePlay.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
const int TurretFire::Price = 30;
TurretFire::TurretFire(float x, float y) :
    Turret("play/turret-3.png", x, y, Price, 0.5) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}
void TurretFire::CreateBullet() {
    Engine::Point diff = Engine::Point(1,0);
    float rotation = ALLEGRO_PI / 2;
    getPlayScene()->BulletGroup->AddNewObject(new BulletFire(Position , diff, rotation, this));
    AudioHelper::PlayAudio("gun.wav");
}
