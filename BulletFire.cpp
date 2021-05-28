#include "BulletFire.hpp"

#include <allegro5/base.h>

#include <random>
#include <string>

#include "EffectDirty.hpp"
#include "EffectExplosion.hpp"
#include "Enemy.hpp"
#include "Group.hpp"
#include "Point.hpp"
#include "ScenePlay.hpp"

class Turret;

BulletFire::BulletFire(Engine::Point position, Engine::Point forwardDirection, float rotation, SpriteObject* parentObj) : Bullet("play/bullet-3.png", 500, 1, position, forwardDirection, rotation - ALLEGRO_PI / 2, parentObj) {
}
void BulletFire::OnExplode(SpriteObject* spriteObj) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
    Enemy* enemy = dynamic_cast<Enemy*>(spriteObj);
    getPlayScene()->GroundEffectGroup->AddNewObject(new EffectDirty("play/dirty-1.png", dist(rng), enemy->Position.x, enemy->Position.y));
    getPlayScene()->EffectGroup->AddNewObject(new EffectExplosion(Position.x, Position.y));
}