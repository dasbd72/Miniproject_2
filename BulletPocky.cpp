#include "BulletPocky.hpp"

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

BulletPocky::BulletPocky(Engine::Point position, Engine::Point forwardDirection, float rotation, SpriteObject* parent) : Bullet("play/bullet-2.png", 800, 1, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
}
void BulletPocky::OnExplode(SpriteObject* spriteObj) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(2, 10);
    Enemy* enemy = dynamic_cast<Enemy*>(spriteObj);
    getPlayScene()->GroundEffectGroup->AddNewObject(new EffectDirty("play/dirty-2.png", dist(rng), enemy->Position.x, enemy->Position.y));
    getPlayScene()->EffectGroup->AddNewObject(new EffectExplosion(Position.x, Position.y));
}
