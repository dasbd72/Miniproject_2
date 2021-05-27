#include <set>
#include <string>
#include <allegro5/allegro.h>
#include <memory>

#include "Image.hpp"
#include "Point.hpp"
#include "SpriteObject.hpp"


SpriteObject::SpriteObject(std::string img, float x, float y):Engine::Sprite(img, x, y){}
bool SpriteObject::hasEffect(EFFECT effect) {
    if(effectActived.find(effect) != effectActived.end()) return 1;
    else return 0;
}
float SpriteObject::getEffectTime(EFFECT effect){
    return effectTimeleft[effect];
}
void SpriteObject::addEffect(EFFECT effect, float time) {
    effectActived.insert(effect);
    effectTimeleft[effect] = time;
    return;
}
void SpriteObject::updateEffect(float deltaTime){
    for(auto it = effectTimeleft.begin(); it != effectTimeleft.end(); it++){
        it->second -= deltaTime;
        if(it->second <= 0) effectActived.erase(it->first);
    }
}
