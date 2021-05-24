#include <allegro5/color.h>

#include "EngineGame.hpp"
#include "IScene.hpp"
#include "ScenePlay.hpp"
#include "ButtonTurret.hpp"
ScenePlay* ButtonTurret::getPlayScene() {
	return dynamic_cast<ScenePlay*>(Engine::EngineGame::GetInstance().GetActiveScene());
}
ButtonTurret::ButtonTurret(std::string img, std::string imgIn, Engine::Sprite Turret, float x, float y, int money) :
	ButtonImage(img, imgIn, x, y), money(money), Turret(Turret) {
}
//ButtonTurret::ButtonTurret(std::string img, std::string imgIn, Engine::Sprite Base, Engine::Sprite Turret, float x, float y, int money) :
//	ButtonImage(img, imgIn, x, y), money(money), Base(Base), Turret(Turret) {
//}
void ButtonTurret::Update(float deltaTime) {
	ButtonImage::Update(deltaTime);
	if (getPlayScene()->GetMoney() >= money) {
		Enabled = true;
		Turret.Tint = al_map_rgba(255, 255, 255, 255);
	} else {
		Enabled = false;
		Turret.Tint = al_map_rgba(0, 0, 0, 160);
	}
}
void ButtonTurret::Draw() const {
	ButtonImage::Draw();
	Turret.Draw();
}
