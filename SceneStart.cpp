#include <functional>
#include <memory>
#include <string>

#include "EngineGame.hpp"
#include "ImageButton.hpp"
#include "Label.hpp"
#include "Point.hpp"
#include "Resources.hpp"
#include "SceneStart.hpp"
#include "SceneStageSelect.hpp"

void StartScene::Initialize() {
    int w = Engine::EngineGame::GetInstance().GetScreenSize().x;
    int h = Engine::EngineGame::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton* btn;

    btn = new Engine::ImageButton("start_scene/out.png", "start_scene/in.png", halfW - 200, halfH , 400, 100);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Play", "pirulen.ttf", 48, halfW, halfH +50 , 0, 0, 0, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("Tower Defense", "pirulen.ttf", 108, halfW, halfH/2 , 255, 255, 0, 255, 0.5, 0.5));

}
void StartScene::Terminate() {
	IScene::Terminate();
}
void StartScene::PlayOnClick(int stage) {
    Engine::EngineGame::GetInstance().ChangeScene("stage-select");
}


