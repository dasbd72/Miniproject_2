#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>

#include "AudioHelper.hpp"
#include "EngineGame.hpp"
#include "ButtonImage.hpp"
#include "Label.hpp"
#include "ScenePlay.hpp"
#include "Point.hpp"
#include "Resources.hpp"
#include "Slider.hpp"
#include "SceneStageSelect.hpp"

void SceneStageSelect::Initialize() {
    int w = Engine::EngineGame::GetInstance().GetScreenSize().x;
    int h = Engine::EngineGame::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ButtonImage* btn;
    btn = new Engine::ButtonImage("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&SceneStageSelect::PlayOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Stage 1", "pirulen.ttf", 48, halfW, halfH / 2, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ButtonImage("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&SceneStageSelect::PlayOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Stage 2", "pirulen.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ButtonImage("stage-select/dirt.png", "stage-select/floor.png", w - 210, h - 85, 200, 75);
    btn->SetOnClickCallback(std::bind(&SceneStageSelect::SettingOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("SETTING", "pirulen.ttf", 24, w - 110, h - 52, 0, 0, 0, 255, 0.5, 0.5));

    bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
}
void SceneStageSelect::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}
void SceneStageSelect::PlayOnClick(int stage) {
    ScenePlay* scene = dynamic_cast<ScenePlay*>(Engine::EngineGame::GetInstance().GetScene("play"));
    scene->MapId = stage;
    Engine::EngineGame::GetInstance().ChangeScene("play");
}
void SceneStageSelect::SettingOnClick() {
    Engine::EngineGame::GetInstance().ChangeScene("setting");
}