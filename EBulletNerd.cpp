#include "EBulletNerd.hpp"

#include <allegro5/base.h>

#include <random>
#include <string>

#include "EffectDirty.hpp"
#include "EffectExplosion.hpp"
#include "Group.hpp"
#include "Point.hpp"
#include "ScenePlay.hpp"
#include "Turret.hpp"

EBulletNerd::EBulletNerd(Engine::Point position, Engine::Point forwardDirection, SpriteObject* parent) : Bullet("play/bullet-7.png", 800, 1, position, forwardDirection, ALLEGRO_PI / 2, parent) {}
void EBulletNerd::OnExplode(SpriteObject* spriteObj) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(2, 10);
    Turret* turret = dynamic_cast<Turret*>(spriteObj);
    getPlayScene()->GroundEffectGroup->AddNewObject(new EffectDirty("play/dirty-2.png", dist(rng), turret->Position.x, turret->Position.y));
    getPlayScene()->EffectGroup->AddNewObject(new EffectExplosion(Position.x, Position.y));
}