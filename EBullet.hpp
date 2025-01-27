#ifndef EBulletNerd_HPP
#define EBulletNerd_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
struct Point;
}

class EBullet : public Bullet {
   public:
    explicit EBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, SpriteObject* parentObj, float damage);
    void OnExplode(SpriteObject* obj) override;
};
#endif  // EBulletNerd_HPP