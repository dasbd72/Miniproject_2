#ifndef DIRTYEFFECT_HPP
#define DIRTYEFFECT_HPP
#include <string>

#include "Sprite.hpp"

class ScenePlay;

class DirtyEffect : public Engine::Sprite {
protected:
	float timeSpan;
	float alpha;
	ScenePlay* getPlayScene();
public:
	DirtyEffect(std::string img, float timeSpan, float x, float y);
	void Update(float deltaTime) override;
};
#endif // DIRTYEFFECT_HPP
