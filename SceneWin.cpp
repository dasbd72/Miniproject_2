#include <functional>
#include <string>

#include "AudioHelper.hpp"
#include "EngineGame.hpp"
#include "Image.hpp"
#include "ButtonImage.hpp"
#include "Label.hpp"
#include "ScenePlay.hpp"
#include "Point.hpp"
#include "SceneWin.hpp"

void SceneWin::Initialize() {
	ticks = 0;
	int w = Engine::EngineGame::GetInstance().GetScreenSize().x;
	int h = Engine::EngineGame::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	AddNewObject(new Engine::Image("win/benjamin-sad.png", halfW, halfH, 0, 0, 0.5, 0.5));
	AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 48, halfW, halfH / 4 + 10, 255, 255, 255, 255, 0.5, 0.5));
	Engine::ButtonImage* btn;
	btn = new Engine::ButtonImage("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&SceneWin::BackOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
	bgmId = AudioHelper::PlayAudio("win.wav");
}
void SceneWin::Terminate() {
	IScene::Terminate();
	AudioHelper::StopBGM(bgmId);
}
void SceneWin::Update(float deltaTime) {
	ticks += deltaTime;
	if (ticks > 4 && ticks < 100 &&
		dynamic_cast<ScenePlay*>(Engine::EngineGame::GetInstance().GetScene("play"))->MapId == 2) {
		ticks = 100;
		bgmId = AudioHelper::PlayBGM("happy.ogg");
	}
}
void SceneWin::BackOnClick(int stage) {
	// Change to select scene.
	Engine::EngineGame::GetInstance().ChangeScene("stage-select");
}
