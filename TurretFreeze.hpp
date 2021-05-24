#ifndef TURRETFREEZE_HPP
#define TURRETFREEZE_HPP
#include "Turret.hpp"

class TurretFreeze: public Turret {
public:
    static const int Price;
    TurretFreeze(float x, float y);
    void CreateBullet() override;
};
#endif // TURRETFREEZE_HPP
