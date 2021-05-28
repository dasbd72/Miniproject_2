#include "BulletIceCream.hpp"

#include <allegro5/base.h>

#include <random>
#include <string>

#include "EffectDirty.hpp"
#include "EffectFrozen.hpp"
#include "Enemy.hpp"
#include "Group.hpp"
#include "Point.hpp"
#include "ScenePlay.hpp"

class Turret;

BulletIceCream::BulletIceCream(Engine::Point position, Engine::Point forwardDirection, float rotation, SpriteObject* parentObj) : Bullet("play/bullet-1.png", 500, 1, position, forwardDirection, rotation - ALLEGRO_PI / 2, parentObj) {
    // nTODO 2 (1/8): You can imitate the 2 files: 'BulletFire.hpp', 'BulletFire.cpp' to create a new bullet.
    effectActived.insert(FROZEN);
}
void BulletIceCream::OnExplode(SpriteObject* spriteObj) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
    Enemy* enemy = dynamic_cast<Enemy*>(spriteObj);
    getPlayScene()->GroundEffectGroup->AddNewObject(new EffectDirty("play/dirty-1.png", dist(rng), enemy->Position.x, enemy->Position.y));
    getPlayScene()->EffectGroup->AddNewObject(new EffectFrozen(Position.x, Position.y));
}
