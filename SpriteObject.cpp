#include <set>
#include <string>
#include <allegro5/allegro.h>
#include <memory>

#include "Image.hpp"
#include "Point.hpp"
#include "SpriteObject.hpp"


SpriteObject::SpriteObject(std::string img, float x, float y):Engine::Sprite(img, x, y){}
int SpriteObject::is(EFFECT effect){
    if(effectActived.find(effect) != effectActived.end()) return 1;
    else return 0;
}
