#ifndef TURRETEXPLODE_HPP
#define TURRETEXPLODE_HPP
#include "Turret.hpp"

class TurretExplode : public Turret {
    void CreateBullet() override {}
    void OnExplode() override;

   public:
    static const int Price;
    static const float ExplodeRadius;
    TurretExplode(float x, float y);
    void Draw() const override;
};
#endif  // TURRETEXPLODE_HPP
