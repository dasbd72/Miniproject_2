#ifndef TURRETFIRE_HPP
#define TURRETFIRE_HPP
#include "Turret.hpp"

class TurretFire : public Turret {
   public:
    static const int Price;
    TurretFire(float x, float y);
    void CreateBullet() override;
};
#endif  // TURRETFIRE_HPP
