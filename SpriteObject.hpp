#ifndef SPRITEOBJECT_HPP
#define SPRITEOBJECT_HPP
#include <set>
#include <map>
#include <string>
#include <allegro5/color.h>

#include "Image.hpp"
#include "Point.hpp"
#include "Sprite.hpp"

class SpriteObject: public Engine::Sprite {
public:
    enum EFFECT: signed{
        FROZEN
    };
    /**
     @brief    Constructor
    @param  {string} img path
    @param  {float} x pos
    @param  {float} y pos
    */
    explicit SpriteObject(std::string img, float x, float y);
    /**
     @brief    If effect is on
    @param  {EFFECT}effect
    */
    int is(EFFECT effect);
protected:
    /// Set Object Of Effects
    std::set<EFFECT> effectActived;
    std::map<EFFECT, float> effectTimeleft;
};

#endif