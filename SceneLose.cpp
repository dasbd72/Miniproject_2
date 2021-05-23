#include <functional>
#include <string>

#include "AudioHelper.hpp"
#include "EngineGame.hpp"
#include "Image.hpp"
#include "ImageButton.hpp"
#include "Label.hpp"
#include "SceneLose.hpp"
#include "ScenePlay.hpp"
#include "Point.hpp"

void SceneLose::Initialize() {
	// TODO 1 (2/3): You can imitate the 2 files: 'SceneLose.hpp', 'SceneLose.cpp' to implement your setting scene.
	int w = Engine::EngineGame::GetInstance().GetScreenSize().x;
	int h = Engine::EngineGame::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	AddNewObject(new Engine::Image("lose/benjamin-happy.png", halfW, halfH, 0, 0, 0.5, 0.5));
	AddNewObject(new Engine::Label("You Lose :(", "pirulen.ttf", 48, halfW, halfH / 4 + 10, 255, 255, 255, 255, 0.5, 0.5));
	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&SceneLose::BackOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
    bgmInstance = AudioHelper::PlaySample("astronomia.ogg", false, AudioHelper::BGMVolume, ScenePlay::DangerTime);
}
void SceneLose::Terminate() {
	AudioHelper::StopSample(bgmInstance);
	bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
	IScene::Terminate();
}
void SceneLose::BackOnClick(int stage) {
	// Change to select scene.
	Engine::EngineGame::GetInstance().ChangeScene("stage-select");
}
