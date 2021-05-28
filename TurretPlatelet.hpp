#ifndef TURRETPLATELET_HPP
#define TURRETPLATELET_HPP
#include "Turret.hpp"

class TurretPlatelet : public Turret {
   public:
    static const int Price;
    TurretPlatelet(float x, float y);
    void CreateBullet() override;
    void Update(float deltaTime) override;
};
#endif  // TURRETPLATELET_HPP
