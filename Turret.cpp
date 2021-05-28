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
}
void Turret::HitBy(Engine::IObject* obj) {
    Bullet* bulletObj = dynamic_cast<Bullet*>(obj);
    Enemy* enemyObj = dynamic_cast<Enemy*>(obj);
    auto Scene = getPlayScene();
    if (enemyObj != nullptr) {
        this->hp -= enemyObj->damage;
    } else if (bulletObj != nullptr) {
        if (bulletObj->parentType == "Enemy")
            this->hp -= bulletObj->damage;
    }
    if (this->hp <= 0) {
        OnExplode();
        Scene->TowerGroup->RemoveObject(objectIterator);
        AudioHelper::PlayAudio("explosion.wav");
        Scene->FreeSpace(Position.x, Position.y);
    }
}
void Turret::Update(float deltaTime) {
    Sprite::Update(deltaTime);
    ScenePlay* scene = getPlayScene();
    if (!Enabled)
        return;
    if (reload > 0) reload -= deltaTime;
    if (Target) {
        if (Target->Position.x < Position.x && Target->Position.y >= Position.y && Target->Position.y < Position.y + scene->BlockSize) {
            Target->lockedTurrets.erase(lockedTurretIterator);
            Target = nullptr;
            lockedTurretIterator = std::list<Turret*>::iterator();
        }
        // Shoot reload.
        if (reload <= 0) {
            // shoot.
            reload = coolDown;
            CreateBullet();
        }
    }
    if (!Target) {
        // Lock first seen target.
        // Can be improved by Spatial Hash, Quad Tree, ...
        // However simply loop through all enemies is enough for this program.
        for (auto& it : scene->EnemyGroup->GetObjects()) {
            if (it->Position.x > Position.x && it->Position.y >= Position.y && it->Position.y < Position.y + scene->BlockSize) {
                Target = dynamic_cast<Enemy*>(it);
                Target->lockedTurrets.push_back(this);
                lockedTurretIterator = std::prev(Target->lockedTurrets.end());
                break;
            }
        }
    }
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
        // Draw target radius.
        al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(0, 0, 255), 2);
    }
}
int Turret::GetPrice() const {
    return price;
}
