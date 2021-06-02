#include "TurretExplode.hpp"

#include <allegro5/allegro_primitives.h>
#include <allegro5/base.h>

#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "BulletFire.hpp"
#include "Collider.hpp"
#include "Enemy.hpp"
#include "Group.hpp"
#include "Point.hpp"
#include "ScenePlay.hpp"
#include "Turret.hpp"

const int TurretExplode::Price = 50;
const float TurretExplode::ExplodeRadius = 225;
void TurretExplode::OnExplode() {
    Turret::OnExplode();
    ScenePlay* scene = getPlayScene();
    for (auto& it : getPlayScene()->EnemyGroup->GetObjects()) {
        Enemy* enemy = dynamic_cast<Enemy*>(it);
        if (Engine::Collider::IsCircleOverlap(Position, ExplodeRadius, enemy->Position, enemy->CollisionRadius))
            enemy->HitBy(this);
    }
}

TurretExplode::TurretExplode(float x, float y) : Turret("play/turret-5.png", x, y, 30, 1, Price, 0.7) {
    name = "TurretExplode";
}
void TurretExplode::Draw() const {
    Turret::Draw();
    al_draw_circle(Position.x, Position.y, ExplodeRadius, al_map_rgb(255, 0, 0), 2);
}