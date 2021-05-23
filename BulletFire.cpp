#include <allegro5/base.h>
#include <random>
#include <string>

#include "DirtyEffect.hpp"
#include "Enemy.hpp"
#include "BulletFire.hpp"
#include "Group.hpp"
#include "ScenePlay.hpp"
#include "Point.hpp"

class Turret;

BulletFire::BulletFire(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent) :
	Bullet("play/bullet-3.png", 500, 1, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
}
void BulletFire::OnExplode(Enemy* enemy) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
	getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-1.png", dist(rng), enemy->Position.x, enemy->Position.y));
}