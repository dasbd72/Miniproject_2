#ifndef TURRETREMOVE_HPP
#define TURRETREMOVE_HPP
#include <string>

#include "Turret.hpp"

class TurretRemove : public Turret {
    void CreateBullet() override {}

   public:
    static const int Price;
    TurretRemove(float x, float y);
};
#endif  // TURRETEXPLODE_HPP
