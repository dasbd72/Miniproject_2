#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "BulletIceCream.hpp"
#include "Group.hpp"
#include "TurretFire.hpp"
#include "ScenePlay.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
const int TurretFire::Price = 30;
TurretFire::TurretFire(float x, float y) :
    // TODO 2 (2/8): You can imitate the 2 files: 'TurretFire.hpp', 'TurretFire.cpp' to create a new turret.
	Turret("play/turret-1.png", x, y, Price, 0.5) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}
void TurretFire::CreateBullet() {
	Engine::Point diff = Engine::Point(1,0);
	float rotation = ALLEGRO_PI / 2;
	getPlayScene()->BulletGroup->AddNewObject(new BulletIceCream(Position , diff, rotation, this));
	AudioHelper::PlayAudio("gun.wav");
}
