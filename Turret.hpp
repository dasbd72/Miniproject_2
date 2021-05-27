#ifndef TURRET_HPP
#define TURRET_HPP
#include <allegro5/base.h>

#include <list>
#include <string>
#include <vector>

#include "Point.hpp"
#include "SpriteObject.hpp"

class Enemy;
class ScenePlay;
class Bullet;

class Turret : public SpriteObject {
    friend class Enemy;
    friend class Bullet;

   protected:
    int price;
    float hp;
    float coolDown;
    float reload = 0;
    float rotateRadian = 2 * ALLEGRO_PI;
    std::list<Turret*>::iterator lockedTurretIterator;
    ScenePlay* getPlayScene();
    // Reference: Design Patterns - Factory Method.
    virtual void CreateBullet() = 0;
    virtual void OnExplode();

   public:
    bool Enabled = true;
    bool Preview = false;
    Enemy* Target = nullptr;
    /**
     * @brief Construct a new Turret object
     * 
     * @param imgTurret Img path of turret
     * @param x 
     * @param y 
     * @param radius 
     * @param hp 
     * @param price 
     * @param coolDown 
     */
    Turret(std::string imgTurret, float x, float y, float radius, float hp, int price, float coolDown);
    /**
     * @brief Update overridden
     * 
     * @param deltaTime 
     */
    void HitBy(Engine::IObject* obj) override;
    void Update(float deltaTime) override;
    /**
     * @brief Draw Overriden
     * 
     */
    void Draw() const override;
    int GetPrice() const;
};
#endif  // TURRET_HPP
