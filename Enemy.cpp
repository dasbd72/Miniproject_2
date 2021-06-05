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
void Enemy::CreateBullet() {
}
Turret *Enemy::getTurretTarget() {
    Turret *turretTarget = nullptr;
    for (auto &it : getPlayScene()->TowerGroup->GetObjects()) {
        Turret *turret = dynamic_cast<Turret *>(it);
        if (!turret->Visible || getPlayScene()->getLane(turret->Position.y) != getPlayScene()->getLane(Position.y) || turret->Position.x >= this->Position.x)
            continue;
        if (((turret->Position - this->Position).Magnitude() <= atkRadius) && (!turretTarget || (turretTarget->Position - this->Position).MagnitudeSquared() > (turret->Position - this->Position).MagnitudeSquared())) {
            turretTarget = turret;
        }
    }
    return turretTarget;
}
Enemy::Enemy(std::string img, float x, float y, float radius, float speed, float hp, int money, float damage, float atkRadius, float coolDown = 5) : SpriteObject(img, x, y), speed(speed), hp(hp), money(money), damage(damage), atkRadius(atkRadius), coolDown(coolDown) {
    CollisionRadius = radius;
    reachEndTime = 0;
    Velocity = Engine::Point(speed, 0);
    target = Engine::Point(ScenePlay::EndGridPointx, static_cast<int>(floor(Position.y / ScenePlay::BlockSize))) * ScenePlay::BlockSize + Engine::Point(ScenePlay::BlockSize / 2, ScenePlay::BlockSize / 2);
    isDead = false;
}
void Enemy::HitBy(NAMES name) {
    switch (name) {
        case _SCENE:
            hp = 0;
            break;
        case _PLANE: {
            if (this->name == _BOSS)
                hp -= 50;
            else
                hp = 0;
            break;
        } break;
        case _BULLETFROZEN: {
            hp -= 1;
            addEffect(FROZEN, 2);
            break;
        }
        case _BULLETFIRE:
            hp -= 1;
            break;
        case _BULLETPLATELET:
            hp -= 1;
            break;
        case _TURRETEXPLODE: {
            if (this->name == _BOSS)
                hp -= 50;
            else
                hp = 0;
            break;
        }
        default:
            break;
    }
    if (hp <= 0) {
        OnExplode();
        // Remove all turret's reference to target.
        for (auto &it : lockedTurrets)
            it->Target = nullptr;
        for (auto &it : lockedBullets)
            it->Target = nullptr;
        getPlayScene()->EarnMoney(money);
        // getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
        isDead = true;
        AudioHelper::PlayAudio("explosion.wav");
    }
}
void Enemy::HitBy(float damage) {
    hp -= damage;
    if (hp <= 0) {
        OnExplode();
        // Remove all turret's reference to target.
        for (auto &it : lockedTurrets)
            it->Target = nullptr;
        for (auto &it : lockedBullets)
            it->Target = nullptr;
        getPlayScene()->EarnMoney(money);
        // getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
        isDead = true;
        AudioHelper::PlayAudio("explosion.wav");
    }
}
void Enemy::Update(float deltaTime) {
    if (isDead) {
        getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
        return;
    }
    SpriteObject::updateEffect(deltaTime);
    float remainSpeed = speed * (hasEffect(FROZEN) ? 0.25 : 1);
    Turret *targetTurret = getTurretTarget();
    if (reload > 0) reload -= deltaTime;
    if (targetTurret != nullptr) {
        remainSpeed = 0;
        if (reload <= 0) {
            // shoot.
            reload = coolDown;
            CreateBullet();
        }
    }
    Velocity = Engine::Point(remainSpeed, 0);
    Position.x -= Velocity.x * deltaTime;
    Position.y += Velocity.y * deltaTime;
    if (Position.x <= ScenePlay::EndGridPointx * ScenePlay::BlockSize + ScenePlay::BlockSize / 2) {
        HitBy(_SCENE);
        getPlayScene()->HitBy();
        reachEndTime = 0;
        return;
    }
    reachEndTime = remainSpeed == 0 ? INFINITY : ((target - Position).Magnitude() - remainSpeed * deltaTime) / remainSpeed;
}
void Enemy::Draw() const {
    Sprite::Draw();
    if (ScenePlay::DebugMode) {
        // Draw collision radius.
        al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
    }
}
