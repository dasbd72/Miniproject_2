#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP
#include <allegro5/allegro_audio.h>

#include <list>
#include <memory>
#include <tuple>
#include <utility>
#include <vector>

#include "IScene.hpp"
#include "Point.hpp"

class Turret;
namespace Engine {
class Group;
class Image;
class Label;
class Sprite;
}  // namespace Engine

class ScenePlay final : public Engine::IScene {
   private:
    enum TileType {
        TILE_DIRT,
        TILE_FLOOR,
        TILE_OCCUPIED,
    };
    ALLEGRO_SAMPLE_ID bgmId;
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> deathBGMInstance;
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bossBGMInstance;

   protected:
    int lives;
    int money;
    int SpeedMult;

    // Stage 2
    int GameStage;
    float BossWaitTime;
    bool BossSpawned;

   public:
    static bool DebugMode;
    static const std::vector<Engine::Point> directions;
    static const int MapWidth, MapHeight;
    static const int BlockSize;
    static const int SpawnGridPointx;
    static const int EndGridPointx;
    static const float DangerTime;
    static const std::vector<int> code;
    int MapId;
    float ticks;
    float deathCountDown;
    // Map tiles.
    Group* TileMapGroup;
    Group* GroundEffectGroup;
    Group* DebugIndicatorGroup;
    Group* BulletGroup;
    Group* TowerGroup;
    Group* EnemyGroup;
    Group* EffectGroup;
    Group* UIGroup;
    Engine::Label* UIMoney;
    Engine::Label* UILives;
    Engine::Image* imgTarget;
    Engine::Sprite* dangerIndicator;
    Turret* preview;
    std::vector<std::vector<TileType>> mapState;
    std::vector<int> laneNum;
    std::list<std::tuple<int, float, int>> enemyWaveData;
    std::list<int> keyStrokes;
    static Engine::Point GetClientSize();
    explicit ScenePlay() = default;
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void Draw() const override;
    void OnMouseDown(int button, int mx, int my) override;
    void OnMouseMove(int mx, int my) override;
    void OnMouseUp(int button, int mx, int my) override;
    void OnKeyDown(int keyCode) override;
    void HitBy();
    void HitBy(bool oneKill);
    int GetMoney() const;
    void EarnMoney(int money);
    void ReadMap();
    void ReadEnemyWave();
    void ConstructUI();
    void UIBtnClicked(int id);
    bool CheckSpaceValid(int x, int y);
    void FreeSpace(int x, int y);
    int getLane(int y);
    std::vector<std::vector<int>> CalculateBFSDistance();
    int getCurrStage();
    // void ModifyReadMapTiles();
};
#endif  // PLAYSCENE_HPP
