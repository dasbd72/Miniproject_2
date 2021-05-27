#ifndef EBulletNerd_HPP
#define EBulletNerd_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
struct Point;
}

class EBulletNerd : public Bullet {
   public:
    explicit EBulletNerd(Engine::Point position, Engine::Point forwardDirection, SpriteObject* parent);
    void OnExplode(SpriteObject* spriteObj) override;
};
#endif  // EBulletNerd_HPP