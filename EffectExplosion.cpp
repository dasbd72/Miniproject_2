#include "EffectExplosion.hpp"

#include <cmath>
#include <string>

#include "EngineGame.hpp"
#include "Group.hpp"
#include "IScene.hpp"
#include "Resources.hpp"
#include "ScenePlay.hpp"
// nTODO 3 (2/2): You can imitate the 2 files: '"EffectExplosion.hpp', '"EffectExplosion.cpp' to create a Shoot Effect.
ScenePlay* EffectExplosion::getPlayScene() {
    return dynamic_cast<ScenePlay*>(Engine::EngineGame::GetInstance().GetActiveScene());
}
EffectExplosion::EffectExplosion(float x, float y) : Sprite("play/explosion-1.png", x, y), timeTicks(0) {
    for (int i = 1; i <= 5; i++) {
        bmps.push_back(Engine::Resources::GetInstance().GetBitmap("play/explosion-" + std::to_string(i) + ".png"));
    }
}
void EffectExplosion::Update(float deltaTime) {
    timeTicks += deltaTime;
    if (timeTicks >= timeSpan) {
        getPlayScene()->EffectGroup->RemoveObject(objectIterator);
        return;
    }
    int phase = floor(timeTicks / timeSpan * bmps.size());
    bmp = bmps[phase];
    Sprite::Update(deltaTime);
}
