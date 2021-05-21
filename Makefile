# Makefile for Windows
CXX = g++
CXXFLAGS = -std=c++11 -IC:\allegro-x86_64-w64-mingw32-gcc-10.2.0-posix-seh-static-5.2.7.0\include -O2
LDFLAGS = -lm -Wall -Wextra
LDLIBS = -LC:\allegro-x86_64-w64-mingw32-gcc-10.2.0-posix-seh-static-5.2.7.0\lib -lallegro_monolith
exe = TowerDefense.exe
obj = Allegro5Exception.o AudioHelper.o Bullet.o Collider.o DirtyEffect.o Enemy.o ExplosionEffect.o GameEngine.o Group.o IceCreamBullet.o IControl.o Image.o ImageButton.o IObject.o IScene.o Label.o LOG.o LoseScene.o NormalEnemy.o Plane.o PlateletTurret.o PlayScene.o PockyBullet.o Point.o Resources.o SettingScene.o Slider.o SofaEnemy.o Sprite.o StageSelectScene.o Start_Scene.o StrongEnemy.o Turret.o TurretButton.o WBCellTurret.o WinScene.o main.o
# FireBullet.o LaserBullet.o LaserTurret.o  MachineGunTurret.o MissileBullet.o MissileTurret.o PlaneEnemy.o SoldierEnemy.o TankEnemy.o

.PHONY: all clean

all: $(obj)
	$(CXX) -o $(exe) $(obj) $(LDFLAGS) $(LDLIBS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	del $(exe) $(obj)

# lm : linker option
# make
# g++ -o TowerDefense.exe Allegro5Exception.o AudioHelper.o Bullet.o Collider.o DirtyEffect.o Enemy.o ExplosionEffect.o GameEngine.o Group.o IceCreamBullet.o IControl.o Image.o ImageButton.o IObject.o IScene.o Label.o LOG.o LoseScene.o NormalEnemy.o Plane.o PlateletTurret.o PlayScene.o PockyBullet.o Point.o Resources.o Slider.o SofaEnemy.o Sprite.o StageSelectScene.o Start_Scene.o StrongEnemy.o Turret.o TurretButton.o WBCellTurret.o WinScene.o main.o -lm -Wall -Wextra -LC:\allegro-x86_64-w64-mingw32-gcc-10.2.0-posix-seh-static-5.2.7.0\lib -lallegro_monolith