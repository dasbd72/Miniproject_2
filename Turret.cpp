#include "Turret.hpp"

#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>

#include <cmath>
#include <random>
#include <string>
#include <utility>
#include <vector>

#include "AudioHelper.hpp"
#include "Bullet.hpp"
#include "Collider.hpp"
#include "EffectDirty.hpp"
#include "Enemy.hpp"
#include "EngineGame.hpp"
#include "Group.hpp"
#include "IObject.hpp"
#include "IScene.hpp"
#include "Point.hpp"
#include "ScenePlay.hpp"
#include "SpriteObject.hpp"

ScenePlay* Turret::getPlayScene() {
    return dynamic_cast<ScenePlay*>(Engine::EngineGame::GetInstance().GetActiveScene());
}
Turret::Turret(std::string imgTurret, float x, float y, float radius, float hp, int price, float coolDown) : SpriteObject(imgTurret, x, y), price(price), coolDown(coolDown), hp(hp) {
    CollisionRadius = radius;
    isDead = false;
    name = _TURRET;
}
void Turret::HitBy(NAMES name) {
    auto Scene = getPlayScene();
    switch (name) {
        case _BOSS:
            hp = 0;
            break;
        case _EBULLET:
            hp -= 1;
            break;
        case _REMOVE:
            hp = 0;
            break;
        default:
            break;
    }
    if (this->hp <= 0) {
        OnExplode();
        Scene->FreeSpace(Position.x, Position.y);
        // Scene->TowerGroup->RemoveObject(objectIterator);
        isDead = true;
        AudioHelper::PlayAudio("explosion.wav");
    }
}
void Turret::HitBy(float damage) {
    auto Scene = getPlayScene();
    hp -= damage;
    if (this->hp <= 0) {
        OnExplode();
        Scene->FreeSpace(Position.x, Position.y);
        // Scene->TowerGroup->RemoveObject(objectIterator);
        isDead = true;
        AudioHelper::PlayAudio("explosion.wav");
    }
}
void Turret::Update(float deltaTime) {
    if (isDead) {
        getPlayScene()->TowerGroup->RemoveObject(objectIterator);
        return;
    }
    Sprite::Update(deltaTime);
    ScenePlay* scene = getPlayScene();
    if (!Enabled)
        return;
    if (reload > 0) reload -= deltaTime;

    bool hasTarget = false;
    if (scene->getCurrStage() == 2 && scene->getLane(this->Position.y) > 0 && scene->getLane(this->Position.y) < 5) hasTarget = true;
    for (auto& it : scene->EnemyGroup->GetObjects()) {
        if (it->Position.x > this->Position.x && scene->getLane(it->Position.y) == scene->getLane(this->Position.y)) {
            hasTarget = true;
            break;
        }
    }
    if (hasTarget) {
        if (reload <= 0) {
            // shoot.
            reload = coolDown;
            CreateBullet();
        }
    }
    // if (Target) {
    //     if (Target->Position.x < Position.x && Target->Position.y >= Position.y && Target->Position.y < Position.y + scene->BlockSize) {
    //         Target->lockedTurrets.erase(lockedTurretIterator);
    //         Target = nullptr;
    //         lockedTurretIterator = std::list<Turret*>::iterator();
    //     }
    //     // Shoot reload.
    //     if (reload <= 0) {
    //         // shoot.
    //         reload = coolDown;
    //         CreateBullet();
    //     }
    // }
    // if (!Target) {
    //     // Lock first seen target.
    //     // Can be improved by Spatial Hash, Quad Tree, ...
    //     // However simply loop through all enemies is enough for this program.
    //     for (auto& it : scene->EnemyGroup->GetObjects()) {
    //         Enemy* enemy = dynamic_cast<Enemy*>(it);
    //         if (enemy->isDead)
    //             continue;
    //         if (it->Position.x > Position.x && it->Position.y >= Position.y && it->Position.y < Position.y + scene->BlockSize) {
    //             Target = dynamic_cast<Enemy*>(it);
    //             Target->lockedTurrets.push_back(this);
    //             lockedTurretIterator = std::prev(Target->lockedTurrets.end());
    //             break;
    //         }
    //     }
    // }
}
void Turret::OnExplode() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distId(1, 3);
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 20);
    for (int i = 0; i < 10; i++) {
        // Random add 10 dirty effects.
        getPlayScene()->GroundEffectGroup->AddNewObject(new EffectDirty("play/dirty-" + std::to_string(distId(rng)) + ".png", dist(rng), Position.x, Position.y));
    }
}
void Turret::Draw() const {
    // if (Preview) {
    //     al_draw_filled_circle(Position.x, Position.y, CollisionRadius, al_map_rgba(0, 255, 0, 50));
    // }
    Sprite::Draw();
    if (ScenePlay::DebugMode) {
        // Draw target radius.        al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(0, 0, 255), 2);
    }
}
int Turret::GetPrice() const {
    return price;
}
Turret::NAMES Turret::GetName() const {
    return name;
}
