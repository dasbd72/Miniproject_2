#ifndef POCKYBULLET_HPP
#define POCKYBULLET_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class BulletPocky : public Bullet {
   public:
    explicit BulletPocky(Engine::Point position, Engine::Point forwardDirection, float rotation, SpriteObject* parent);
    void OnExplode(SpriteObject* spriteObj) override;
};
#endif  // POCKYBULLET_HPP
