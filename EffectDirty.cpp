#include "EffectDirty.hpp"

#include <allegro5/base.h>
#include <allegro5/color.h>

#include <random>

#include "EngineGame.hpp"
#include "Group.hpp"
#include "IScene.hpp"
#include "ScenePlay.hpp"

ScenePlay* EffectDirty::getPlayScene() {
    return dynamic_cast<ScenePlay*>(Engine::EngineGame::GetInstance().GetActiveScene());
}
EffectDirty::EffectDirty(std::string img, float timeSpan, float x, float y) : Engine::Sprite(img, x, y), timeSpan(timeSpan), alpha(1) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist(-ALLEGRO_PI, ALLEGRO_PI);
    Rotation = dist(rng);
}
void EffectDirty::Update(float deltaTime) {
    alpha -= deltaTime / timeSpan;
    if (alpha <= 0) {
        getPlayScene()->GroundEffectGroup->RemoveObject(objectIterator);
        return;
    }
    unsigned char r, g, b, a = alpha * 255;
    al_unmap_rgb(Tint, &r, &g, &b);
    Tint = al_map_rgba(r, g, b, a);
    Sprite::Update(deltaTime);
}
