#ifndef DIRTYEFFECT_HPP
#define DIRTYEFFECT_HPP
#include <string>

#include "Sprite.hpp"

class ScenePlay;

class EffectDirty : public Engine::Sprite {
protected:
	float timeSpan;
	float alpha;
	ScenePlay* getPlayScene();
public:
	EffectDirty(std::string img, float timeSpan, float x, float y);
	void Update(float deltaTime) override;
};
#endif // DIRTYEFFECT_HPP
