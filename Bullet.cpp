#include "Bullet.hpp"

#include "Collider.hpp"
#include "Enemy.hpp"
#include "EngineGame.hpp"
#include "Group.hpp"
#include "IObject.hpp"
#include "IScene.hpp"
#include "Point.hpp"
#include "ScenePlay.hpp"
#include "SpriteObject.hpp"
#include "Turret.hpp"

ScenePlay* Bullet::getPlayScene() {
    return dynamic_cast<ScenePlay*>(Engine::EngineGame::GetInstance().GetActiveScene());
}
void Bullet::OnExplode(SpriteObject* spriteObj) {
}
Bullet::Bullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, SpriteObject* parentObj) : SpriteObject(img, position.x, position.y), speed(speed), damage(damage), parentObj(parentObj) {
    Velocity = forwardDirection * speed;
    Rotation = rotation;
    CollisionRadius = 4;
    if (dynamic_cast<Turret*>(parentObj))
        parentType = "Turret";
    else if (dynamic_cast<Enemy*>(parentObj))
        parentType = "Enemy";
}
void Bullet::Update(float deltaTime) {
    Sprite::Update(deltaTime);
    ScenePlay* scene = getPlayScene();
    // Can be improved by Spatial Hash, Quad Tree, ...
    // However simply loop through all enemies is enough for this program.
    if (dynamic_cast<Turret*>(this->parentObj) != nullptr) {
        for (auto& it : scene->EnemyGroup->GetObjects()) {
            Enemy* enemy = dynamic_cast<Enemy*>(it);
            if (!enemy->Visible)
                continue;
            if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, enemy->Position, enemy->CollisionRadius)) {
                OnExplode(enemy);
                enemy->HitBy(this);
                getPlayScene()->BulletGroup->RemoveObject(objectIterator);
                return;
            }
        }
    } else if (dynamic_cast<Enemy*>(this->parentObj) != nullptr) {
        for (auto& it : scene->TowerGroup->GetObjects()) {
            Turret* turret = dynamic_cast<Turret*>(it);
            if (!turret->Visible)
                continue;
            if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, turret->Position, turret->CollisionRadius)) {
                OnExplode(turret);
                turret->HitBy(this);
                getPlayScene()->BulletGroup->RemoveObject(objectIterator);
                return;
            }
        }
    }
    // Check if out of boundary.
    if (!Engine::Collider::IsRectOverlap(Position - Size / 2, Position + Size / 2, Engine::Point(0, 0), ScenePlay::GetClientSize()))
        getPlayScene()->BulletGroup->RemoveObject(objectIterator);
}
