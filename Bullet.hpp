#ifndef BULLET_HPP
#define BULLET_HPP
#include <string>

#include "SpriteObject.hpp"
#include "Enemy.hpp"

class Enemy;
class ScenePlay;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class Bullet : public SpriteObject {
	friend class Enemy;
protected:
	float speed;
	float damage;
	Turret* parent;
	ScenePlay* getPlayScene();
	virtual void OnExplode(Enemy* enemy);
public:
	Enemy* Target = nullptr;
	explicit Bullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void Update(float deltaTime) override;
};
#endif // BULLET_HPP
