#ifndef BULLET_HPP
#define BULLET_HPP
#include <string>

#include "Enemy.hpp"
#include "SpriteObject.hpp"

class Enemy;
class ScenePlay;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class Bullet : public SpriteObject {
    friend class Enemy;
    friend class Turret;

   protected:
    float speed;
    float damage;
    std::string parentType;
    SpriteObject* parentObj;
    ScenePlay* getPlayScene();
    virtual void OnExplode(SpriteObject* spriteObj);

   public:
    Enemy* Target = nullptr;
    explicit Bullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, SpriteObject* parentObj);
    /**
     * @brief Update overridden
     * 
     * @param deltaTime 
     */
    void Update(float deltaTime) override;
};
#endif  // BULLET_HPP
