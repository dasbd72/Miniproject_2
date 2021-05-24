#ifndef TURRETBUTTON_HPP
#define TURRETBUTTON_HPP
#include <string>

#include "ButtonImage.hpp"
#include "Sprite.hpp"

class ScenePlay;

class ButtonTurret : public Engine::ButtonImage {
protected:
    ScenePlay* getPlayScene();
public:
	int money;
	// Engine::Sprite Base;
	Engine::Sprite Turret;
	ButtonTurret(std::string img, std::string imgIn, Engine::Sprite Turret, float x, float y, int money);
	//ButtonTurret(std::string img, std::string imgIn, Engine::Sprite Base, Engine::Sprite Turret, float x, float y, int money);
	void Update(float deltaTime) override;
	void Draw() const override;
};
#endif // TURRETBUTTON_HPP
