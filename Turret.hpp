#ifndef TURRET_HPP
#define TURRET_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "SpriteObject.hpp"

class Enemy;
class ScenePlay;

class Turret: public SpriteObject {
protected:
    int price;
    float coolDown;
    float reload = 0;
    float rotateRadian = 2 * ALLEGRO_PI;
    std::list<Turret*>::iterator lockedTurretIterator;
    ScenePlay* getPlayScene();
    // Reference: Design Patterns - Factory Method.
    virtual void CreateBullet() = 0;

public:
    bool Enabled = true;
    bool Preview = false;
    Enemy* Target = nullptr;
    Turret(/*std::string imgBase,*/std::string imgTurret, float x, float y,/* float radius,*/ int price, float coolDown);
    void Update(float deltaTime) override;
    void Draw() const override;
	int GetPrice() const;
};
#endif // TURRET_HPP
