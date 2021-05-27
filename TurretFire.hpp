#ifndef WBCELLTURRET_HPP
#define WBCELLTURRET_HPP
#include "Turret.hpp"

class TurretFire : public Turret {
   public:
    static const int Price;
    TurretFire(float x, float y);
    void CreateBullet() override;
};
#endif  // WBCELLTURRET_HPP
