#ifndef EXPLOSIONEFFECT_HPP
#define EXPLOSIONEFFECT_HPP
#include <allegro5/bitmap.h>

#include <memory>
#include <vector>

#include "Sprite.hpp"

class ScenePlay;

class EffectExplosion : public Engine::Sprite {
   protected:
    ScenePlay* getPlayScene();
    float timeTicks;
    std::vector<std::shared_ptr<ALLEGRO_BITMAP>> bmps;
    float timeSpan = 0.5;

   public:
    EffectExplosion(float x, float y);
    void Update(float deltaTime) override;
};
#endif  // EXPLOSIONEFFECT_HPP
