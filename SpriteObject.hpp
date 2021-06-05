#ifndef SPRITEOBJECT_HPP
#define SPRITEOBJECT_HPP
#include <allegro5/color.h>

#include <map>
#include <set>
#include <string>

#include "Image.hpp"
#include "Point.hpp"
#include "Sprite.hpp"

class SpriteObject : public Engine::Sprite {
   public:
    float CollisionRadius = 0;
    enum EFFECT : signed {
        FROZEN
    };
    enum NAMES : signed {
        _SCENE,
        _PLANE,
        _TURRET,
        _BULLETFROZEN,
        _BULLETFIRE,
        _BULLETPLATELET,
        _TURRETEXPLODE,
        _REMOVE,
        _EBULLET,
        _BOSS
    };
    NAMES name;
    /**
     * @brief Construct a new Sprite Object object
     * 
     * @param img string path
     * @param x float pos
     * @param y float pos
     */
    explicit SpriteObject(std::string img, float x, float y);
    /**
     * @brief Has effect or not
     * 
     * @param effect 
     * @return true 
     * @return false 
     */
    bool hasEffect(EFFECT effect);
    /**
     * @brief Get Effect Time Left
     * 
     * @param effect 
     * @return float 
     */
    float getEffectTime(EFFECT effect);
    /**
     * @brief Add Effect
     * 
     * @param effect EFFECT 
     * @param time float
     */
    void addEffect(EFFECT effect, float time);
    /**
     * @brief Update Effect time
     * 
     */
    void updateEffect(float deltaTime);

    virtual void HitBy(NAMES name) {}
    virtual void HitBy(float damage){};
    bool isDead = false;

   protected:
    /// Set Object Of Effects
    std::set<EFFECT> effectActived;
    std::map<EFFECT, float> effectTimeleft;
};

#endif