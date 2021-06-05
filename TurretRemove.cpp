#include "TurretRemove.hpp"

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
const int TurretRemove::Price = 0;
TurretRemove::TurretRemove(float x, float y) : Turret("play/bomb.png", x, y, 30, 0, Price, 0) {
    name = _REMOVE;
}