#include <cmath>
#include <string>

#include "EffectFrozen.hpp"
#include "EngineGame.hpp"
#include "Group.hpp"
#include "IScene.hpp"
#include "ScenePlay.hpp"
#include "Resources.hpp"
ScenePlay* EffectFrozen::getPlayScene() {
    return dynamic_cast<ScenePlay*>(Engine::EngineGame::GetInstance().GetActiveScene());
}
EffectFrozen::EffectFrozen(float x, float y) : Sprite("play/frozen-1.png", x, y), timeTicks(0) {
    for (int i = 1; i <= 5; i++) {
        bmps.push_back(Engine::Resources::GetInstance().GetBitmap("play/frozen-" + std::to_string(i) + ".png"));
    }
}
void EffectFrozen::Update(float deltaTime) {
    timeTicks += deltaTime;
    if (timeTicks >= timeSpan) {
        getPlayScene()->EffectGroup->RemoveObject(objectIterator);
        return;
    }
    int phase = floor(timeTicks / timeSpan * bmps.size());
    bmp = bmps[phase];
    Sprite::Update(deltaTime);
}
