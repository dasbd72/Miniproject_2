#include "TurretPlatelet.hpp"

#include <allegro5/base.h>

#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "BulletPocky.hpp"
#include "EffectShoot.hpp"
#include "Enemy.hpp"
#include "Group.hpp"
#include "Point.hpp"
#include "ScenePlay.hpp"
#include "Turret.hpp"
const int TurretPlatelet::Price = 50;
TurretPlatelet::TurretPlatelet(float x, float y) : Turret("play/turret-2.png", x, y, 20, 50, Price, 0.7) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}
void TurretPlatelet::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    Engine::Point normal = Engine::Point(-normalized.y, normalized.x);
    // Change bullet position to the front of the gun barrel.
    // nTODO 3 (1/2): Add a Shoot Effect here.
    getPlayScene()->EffectGroup->AddNewObject(new EffectShoot(Position.x + cos(rotation) * 50, Position.y + sin(rotation) * 50));
    getPlayScene()->BulletGroup->AddNewObject(new BulletPocky(Position + normalized * 36 - normal * 6, diff, rotation, this));
    getPlayScene()->BulletGroup->AddNewObject(new BulletPocky(Position + normalized * 36 + normal * 6, diff, rotation, this));
    AudioHelper::PlayAudio("laser.wav");
}
void TurretPlatelet::Update(float deltaTime) {
    if (isDead) {
        getPlayScene()->TowerGroup->RemoveObject(objectIterator);
        return;
    }

    Sprite::Update(deltaTime);
    ScenePlay* scene = getPlayScene();
    if (!Enabled)
        return;
    if (Target) {
        if (Target->Position.x < Position.x) {
            Target->lockedTurrets.erase(lockedTurretIterator);
            Target = nullptr;
            lockedTurretIterator = std::list<Turret*>::iterator();
        }
    }
    if (!Target) {
        // Lock first seen target.
        // Can be improved by Spatial Hash, Quad Tree, ...
        // However simply loop through all enemies is enough for this program.
        int ty = scene->getLane(this->Position.y);
        int ey;
        for (auto& it : scene->EnemyGroup->GetObjects()) {
            Enemy* enemy = dynamic_cast<Enemy*>(it);
            if (enemy->isDead)
                continue;
            ey = scene->getLane(it->Position.y);
            if (it->Position.x > Position.x && ey >= ty - 1 && ey <= ty + 1) {
                Target = dynamic_cast<Enemy*>(it);
                Target->lockedTurrets.push_back(this);
                lockedTurretIterator = std::prev(Target->lockedTurrets.end());
                break;
            }
        }
    }
    if (Target) {
        Engine::Point originRotation = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
        Engine::Point targetRotation = (Target->Position - Position).Normalize();
        float maxRotateRadian = rotateRadian * deltaTime;
        float cosTheta = originRotation.Dot(targetRotation);
        // Might have floating-point precision error.
        if (cosTheta > 1)
            cosTheta = 1;
        else if (cosTheta < -1)
            cosTheta = -1;
        float radian = acos(cosTheta);
        Engine::Point rotation;
        if (abs(radian) <= maxRotateRadian)
            rotation = targetRotation;
        else
            rotation = ((abs(radian) - maxRotateRadian) * originRotation + maxRotateRadian * targetRotation) / radian;
        // Add 90 degrees (PI/2 radian), since we assume the image is oriented upward.
        Rotation = atan2(rotation.y, rotation.x) + ALLEGRO_PI / 2;
        // Shoot reload.
        reload -= deltaTime;
        if (reload <= 0) {
            // shoot.
            reload = coolDown;
            CreateBullet();
        }
    }
}
