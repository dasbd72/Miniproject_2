#include "TurretTank.hpp"

#include <allegro5/base.h>

#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "BulletFire.hpp"
#include "Enemy.hpp"
#include "Group.hpp"
#include "Point.hpp"
#include "ScenePlay.hpp"
#include "Turret.hpp"
const int TurretTank::Price = 10;
TurretTank::TurretTank(float x, float y) : Turret("play/turret-4.png", x, y, 30, 100, Price, 0.7) {
}