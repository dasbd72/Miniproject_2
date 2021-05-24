#include <cmath>
#include <string>

#include "EffectShoot.hpp"
#include "EngineGame.hpp"
#include "Group.hpp"
#include "IScene.hpp"
#include "ScenePlay.hpp"
#include "Resources.hpp"
ScenePlay* EffectShoot::getPlayScene() {
    return dynamic_cast<ScenePlay*>(Engine::EngineGame::GetInstance().GetActiveScene());
}
EffectShoot::EffectShoot(float x, float y) : Sprite("play/shoot-1.png", x, y), timeTicks(0) {
    for (int i = 1; i <= 4; i++) {
        bmps.push_back(Engine::Resources::GetInstance().GetBitmap("play/shoot-" + std::to_string(i) + ".png"));
    }
}
void EffectShoot::Update(float deltaTime) {
    timeTicks += deltaTime;
    if (timeTicks >= timeSpan) {
        getPlayScene()->EffectGroup->RemoveObject(objectIterator);
        return;
    }
    int phase = floor(timeTicks / timeSpan * bmps.size());
    bmp = bmps[phase];
    Sprite::Update(deltaTime);
}
