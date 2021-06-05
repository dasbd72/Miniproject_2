#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <list>
#include <string>
#include <vector>

#include "Point.hpp"
#include "SpriteObject.hpp"

class Bullet;
class ScenePlay;
class Turret;

class Enemy : public SpriteObject {
    friend class Turret;
    friend class Bullet;

   protected:
    Engine::Point target;
    float speed;
    float hp;
    float damage;
    float atkRadius;
    float coolDown;
    float reload = 0;
    int money;
    ScenePlay* getPlayScene();
    virtual void OnExplode();
    virtual void CreateBullet();
    virtual Turret* getTurretTarget();

   public:
    float reachEndTime;
    std::list<Turret*> lockedTurrets;
    std::list<Bullet*> lockedBullets;
    /**
     * @brief Construct a new Enemy object
     * 
     * @param img 
     * @param x 
     * @param y 
     * @param radius 
     * @param speed 
     * @param hp 
     * @param money 
     * @param damage 
     * @param atkRadius 
     */
    Enemy(std::string img, float x, float y, float radius, float speed, float hp, int money, float damage, float atkRadius, float coolDown);
    /**
     * @brief Enemy HitBy name
     * 
     * @param name 
     */
    void HitBy(NAMES name) override;
    /**
     * @brief Update Overridden
     * 
     * @param deltaTime 
     */
    void HitBy(float damage) override;
    void Update(float deltaTime) override;
    /**
     * @brief Draw overriden
     */
    void Draw() const override;
};
#endif  // ENEMY_HPP
