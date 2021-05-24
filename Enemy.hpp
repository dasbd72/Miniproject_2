#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <list>
#include <vector>
#include <string>

#include "Point.hpp"
#include "SpriteObject.hpp"

class Bullet;
class ScenePlay;
class Turret;

class Enemy : public SpriteObject {
protected:
	Engine::Point target;
	float speed;
	float hp;
	int money;
	ScenePlay* getPlayScene();
	virtual void OnExplode();
public:
	float reachEndTime;
	std::list<Turret*> lockedTurrets;
	std::list<Bullet*> lockedBullets;
	Enemy(std::string img, float x, float y, float radius, float speed, float hp, int money );
 	void Hit(Engine::IObject *obj);
	void Update(float deltaTime) override;
	void Draw() const override;
};
#endif // ENEMY_HPP
