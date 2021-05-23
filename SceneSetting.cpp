#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>
#include <iostream>

#include "AudioHelper.hpp"
#include "EngineGame.hpp"
#include "ImageButton.hpp"
#include "Label.hpp"
#include "ScenePlay.hpp"
#include "Point.hpp"
#include "Resources.hpp"
#include "Slider.hpp"
#include "SceneSetting.hpp"

void SceneSetting::Initialize(){
	int w = Engine::EngineGame::GetInstance().GetScreenSize().x;
    int h = Engine::EngineGame::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
    int halfH = h / 2;


	// TODO 1 (3/3): Move the sliderBGM, sliderSFX to the setting Scene and make sure the background music will be played
    Slider *sliderBGM, *sliderSFX;
    sliderBGM = new Slider(40 + halfW - 95, halfH - 50 - 2, 190, 4);
    sliderBGM->SetOnValueChangedCallback(std::bind(&SceneSetting::BGMSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderBGM);
    AddNewObject(new Engine::Label("BGM: ", "pirulen.ttf", 28, 40 + halfW - 60 - 95, halfH - 50, 255, 255, 255, 255, 0.5, 0.5));
    
	sliderSFX = new Slider(40 + halfW - 95, halfH + 50 - 2, 190, 4);
    sliderSFX->SetOnValueChangedCallback(std::bind(&SceneSetting::SFXSlideOnValueChanged, this, std::placeholders::_1));
    AddNewControlObject(sliderSFX);
    AddNewObject(new Engine::Label("SFX: ", "pirulen.ttf", 28, 40 + halfW - 60 - 95, halfH + 50, 255, 255, 255, 255, 0.5, 0.5));
	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", w - 210, h - 85, 200, 75);
    btn->SetOnClickCallback(std::bind(&SceneSetting::ReturnOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Return", "pirulen.ttf", 24, w - 110, h - 52, 0, 0, 0, 255, 0.5, 0.5));
    // Not safe if release resource while playing, however we only free while change scene, so it's fine.
	std::cout << "[Volume]" << AudioHelper::BGMVolume << std::endl;
	bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
	sliderBGM->SetValue(AudioHelper::BGMVolume);
    sliderSFX->SetValue(AudioHelper::SFXVolume);
}
void SceneSetting::Terminate(){
	AudioHelper::StopSample(bgmInstance);
	bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
	IScene::Terminate();
}
void SceneSetting::ReturnOnClick(){
    Engine::EngineGame::GetInstance().ChangeScene("stage-select");
}
void SceneSetting::BGMSlideOnValueChanged(float value){
	AudioHelper::ChangeSampleVolume(bgmInstance, value);
    AudioHelper::BGMVolume = value;
}
void SceneSetting::SFXSlideOnValueChanged(float value){
    AudioHelper::SFXVolume = value;
}