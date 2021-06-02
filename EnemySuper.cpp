#include "EnemySuper.hpp"

#include <string>

#include "AudioHelper.hpp"
#include "Collider.hpp"
#include "EBullet.hpp"
#include "EnemyStrong.hpp"
#include "Resources.hpp"
#include "ScenePlay.hpp"
#include "Turret.hpp"

const float EnemySuper::ExplosionRadius = 200;
EnemySuper::EnemySuper(int x, int y) : Enemy("play/boss-0.png", x, y, 220, 10, 2000, 500, 10000, 250, 20) {
    BossStage = 0;
    name = "EnemySuper";
}
void EnemySuper::Update(float deltaTime) {
    SpriteObject::updateEffect(deltaTime);
    Sprite::Image::Update(deltaTime);
    float remainSpeed = speed * (hasEffect(FROZEN) ? 0.25 : 1);
    ScenePlay* scene = getPlayScene();
    Turret* turret;

    for (auto& it : scene->TowerGroup->GetObjects()) {
        Turret* turret = dynamic_cast<Turret*>(it);
        if (!turret->Visible)
            continue;
        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, turret->Position, turret->CollisionRadius)) {
            turret->HitBy(this);
        }
    }

    if (reload > 0) reload -= deltaTime;
    if (reload <= 0) {
        // shoot.
        reload = coolDown;
        for (int i = 5; i >= -5; i -= 2) {
            scene->EnemyGroup->AddNewObject(new EnemyStrong(Position.x - 100, Position.y + 64 * i));
        }
    }

    Velocity = Engine::Point(remainSpeed, 0);
    Position.x -= Velocity.x * deltaTime;
    Position.y += Velocity.y * deltaTime;
    if (Position.x <= ScenePlay::EndGridPointx * ScenePlay::BlockSize + ScenePlay::BlockSize / 2) {
        HitBy(getPlayScene());
        getPlayScene()->HitBy(true);
        reachEndTime = 0;
        return;
    }

    if (BossStage == 0 && hp < 500) {
        BossStage = 1;
        bmp = Engine::Resources::GetInstance().GetBitmap("play/boss-3.png");
    } else if (BossStage == 1 && hp < 1000) {
        BossStage = 2;
        bmp = Engine::Resources::GetInstance().GetBitmap("play/boss-2.png");
    } else if (BossStage == 2 && hp < 1500) {
        BossStage = 3;
        bmp = Engine::Resources::GetInstance().GetBitmap("play/boss-1.png");
    }
}