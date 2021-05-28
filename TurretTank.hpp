#ifndef TURRETTANK_HPP
#define TURRETTANK_HPP
#include "Turret.hpp"

class TurretTank : public Turret {
    void CreateBullet() override {}

   public:
    static const int Price;
    TurretTank(float x, float y);
};
#endif  // TURRETEXPLODE_HPP
