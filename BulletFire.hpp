#ifndef FIREBULLET_HPP
#define FIREBULLET_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class BulletFire : public Bullet {
   public:
    explicit BulletFire(Engine::Point position, Engine::Point forwardDirection, float rotation, SpriteObject* parentObj);
    void OnExplode(SpriteObject* spriteObj) override;
};
#endif  // FIREBULLET_HPP
