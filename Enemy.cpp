#include "Enemy.hpp"

#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>

#include <cmath>
#include <random>
#include <string>
#include <vector>

#include "AudioHelper.hpp"
#include "Bullet.hpp"
#include "Collider.hpp"
#include "EffectDirty.hpp"
#include "EngineGame.hpp"
#include "Group.hpp"
#include "IScene.hpp"
#include "LOG.hpp"
#include "Plane.hpp"
#include "ScenePlay.hpp"
#include "SpriteObject.hpp"
#include "Turret.hpp"

ScenePlay *Enemy::getPlayScene() {
    return dynamic_cast<ScenePlay *>(Engine::EngineGame::GetInstance().GetActiveScene());
}
void Enemy::OnExplode() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distId(1, 3);
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 20);
    for (int i = 0; i < 10; i++) {
        // Random add 10 dirty effects.
        getPlayScene()->GroundEffectGroup->AddNewObject(new EffectDirty("play/dirty-" + std::to_string(distId(rng)) + ".png", dist(rng), Position.x, Position.y));
    }
}
Enemy::Enemy(std::string img, float x, float y, float radius, float speed, float hp, int money, float damage, float atkRadius) : SpriteObject(img, x, y), speed(speed), hp(hp), money(money), damage(damage), atkRadius(atkRadius) {
    CollisionRadius = radius;
    reachEndTime = 0;
    Velocity = Engine::Point(speed, 0);
    target = Engine::Point(ScenePlay::EndGridPointx, static_cast<int>(floor(Position.y / ScenePlay::BlockSize))) * ScenePlay::BlockSize + Engine::Point(ScenePlay::BlockSize / 2, ScenePlay::BlockSize / 2);
}
void Enemy::HitBy(Engine::IObject *obj) {

    Bullet *bulletObj = dynamic_cast<Bullet *>(obj);
    Turret *turretObj = dynamic_cast<Turret *>(obj);
    Plane *planeObj = dynamic_cast<Plane *>(obj);
    Engine::IScene *sceneObj = dynamic_cast<Engine::IScene *>(obj);

    if (sceneObj != nullptr || planeObj != nullptr || turretObj != nullptr) {
        hp -= hp;
    } else if (bulletObj != nullptr) {
        hp -= bulletObj->damage;
        if (bulletObj->hasEffect(FROZEN)) addEffect(FROZEN, 2);
    }
    if (hp <= 0) {
        OnExplode();
        // Remove all turret's reference to target.
        for (auto &it : lockedTurrets)
            it->Target = nullptr;
        for (auto &it : lockedBullets)
            it->Target = nullptr;
        getPlayScene()->EarnMoney(money);
        getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
        AudioHelper::PlayAudio("explosion.wav");
    }
}
void Enemy::Update(float deltaTime) {
    SpriteObject::updateEffect(deltaTime);
    float remainSpeed = speed * deltaTime;
    ScenePlay *scene = getPlayScene();

    // Enemy hit turret
    for (auto &it : scene->TowerGroup->GetObjects()) {
        Turret *turret = dynamic_cast<Turret *>(it);
        if (!turret->Visible)
            continue;
        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, turret->Position, turret->CollisionRadius)) {
            turret->HitBy(this);
            this->HitBy(turret);
            return;
        }
    }

    Velocity = Engine::Point(speed * (hasEffect(FROZEN) ? 0.25 : 1), 0);
    Position.x -= Velocity.x * deltaTime;
    Position.y += Velocity.y * deltaTime;
    if (Position.x <= ScenePlay::EndGridPointx * ScenePlay::BlockSize + ScenePlay::BlockSize / 2) {
        HitBy(getPlayScene());
        getPlayScene()->HitBy();
        reachEndTime = 0;
        return;
    }
    Engine::Point vec = target - Position;
    reachEndTime = (vec.Magnitude() - remainSpeed) / speed;
}
void Enemy::Draw() const {
    Sprite::Draw();
    if (ScenePlay::DebugMode) {
        // Draw collision radius.
        al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
    }
}
