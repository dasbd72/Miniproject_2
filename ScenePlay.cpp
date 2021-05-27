#include "ScenePlay.hpp"

#include <allegro5/allegro.h>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <functional>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <string>
#include <vector>

#include "AudioHelper.hpp"
#include "ButtonTurret.hpp"
#include "EffectDirty.hpp"
#include "Enemy.hpp"
#include "EnemyNerd.hpp"
#include "EnemyNormal.hpp"
#include "EnemySofa.hpp"
#include "EnemyStrong.hpp"
#include "EngineGame.hpp"
#include "Group.hpp"
#include "IObject.hpp"
#include "Image.hpp"
#include "LOG.hpp"
#include "Label.hpp"
#include "Plane.hpp"
#include "Resources.hpp"
#include "Sprite.hpp"
#include "Turret.hpp"
#include "TurretFire.hpp"
#include "TurretFreeze.hpp"
#include "TurretPlatelet.hpp"

bool ScenePlay::DebugMode = false;
const std::vector<Engine::Point> ScenePlay::directions = {Engine::Point(-1, 0), Engine::Point(0, -1), Engine::Point(1, 0), Engine::Point(0, 1)};
const int ScenePlay::MapWidth = 12, ScenePlay::MapHeight = 6;  //50;//13;
const int ScenePlay::BlockSize = 128;
const float ScenePlay::DangerTime = 7.61;
const int ScenePlay::SpawnGridPointx = 12;
const int ScenePlay::EndGridPointx = -1;
// nTODO 4 (1/3): Set a cheat sequence here.
const std::vector<int> ScenePlay::code = {ALLEGRO_KEY_UP, ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_DOWN, ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT, ALLEGRO_KEY_ENTER};
Engine::Point ScenePlay::GetClientSize() {
    return Engine::Point(MapWidth * BlockSize, MapHeight * BlockSize);
}
void ScenePlay::Initialize() {
    mapState.clear();
    keyStrokes.clear();
    ticks = 0;
    deathCountDown = -1;
    lives = 10000;
    money = 150;
    SpeedMult = 1;
    laneNum = std::vector<int>(MapHeight);
    std::iota(laneNum.begin(), laneNum.end(), 0);
    // Add groups from bottom to top.
    AddNewObject(TileMapGroup = new Group());
    AddNewObject(GroundEffectGroup = new Group());
    AddNewObject(DebugIndicatorGroup = new Group());
    AddNewObject(TowerGroup = new Group());
    AddNewObject(EnemyGroup = new Group());
    AddNewObject(BulletGroup = new Group());
    AddNewObject(EffectGroup = new Group());
    // Should support buttons.
    AddNewControlObject(UIGroup = new Group());
    ReadMap();
    ReadEnemyWave();
    ConstructUI();
    imgTarget = new Engine::Image("play/target.png", 0, 0);
    imgTarget->Visible = false;
    preview = nullptr;
    UIGroup->AddNewObject(imgTarget);
    // Preload Lose Scene
    deathBGMInstance = Engine::Resources::GetInstance().GetSampleInstance("astronomia.ogg");
    Engine::Resources::GetInstance().GetBitmap("lose/benjamin-happy.png");
    // Start BGM.
    bgmId = AudioHelper::PlayBGM("play.ogg");
}
void ScenePlay::Terminate() {
    AudioHelper::StopBGM(bgmId);
    AudioHelper::StopSample(deathBGMInstance);
    deathBGMInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
    // delete TileMapGroup;
    // delete GroundEffectGroup;
    // delete DebugIndicatorGroup;
    // delete TowerGroup;
    // delete EnemyGroup;
    // delete BulletGroup;
    // delete EffectGroup;
    // delete UIGroup;
    // delete imgTarget;
}
void ScenePlay::Update(float deltaTime) {
    // If we use deltaTime directly, then we might have Bullet-through-paper problem.
    // Reference: Bullet-Through-Paper
    if (SpeedMult == 0)
        deathCountDown = -1;
    else if (deathCountDown != -1)
        SpeedMult = 1;
    // Calculate danger zone.
    std::vector<float> reachEndTimes;
    for (auto& it : EnemyGroup->GetObjects()) {
        reachEndTimes.push_back(dynamic_cast<Enemy*>(it)->reachEndTime);
    }
    // Can use Heap / Priority-Queue instead. But since we won't have too many enemies, sorting is fast enough.
    std::sort(reachEndTimes.begin(), reachEndTimes.end());
    float newDeathCountDown = -1;
    int danger = lives;
    for (auto& it : reachEndTimes) {
        if (it <= DangerTime) {
            danger--;
            if (danger <= 0) {
                // Death Countdown
                float pos = DangerTime - it;
                if (it > deathCountDown) {
                    // Restart Death Count Down BGM.
                    AudioHelper::StopSample(deathBGMInstance);
                    if (SpeedMult != 0)
                        deathBGMInstance = AudioHelper::PlaySample("astronomia.ogg", false, AudioHelper::BGMVolume, pos);
                }
                float alpha = pos / DangerTime;
                alpha = std::max(0, std::min(255, static_cast<int>(alpha * alpha * 255)));
                dangerIndicator->Tint = al_map_rgba(255, 255, 255, alpha);
                newDeathCountDown = it;
                break;
            }
        }
    }
    deathCountDown = newDeathCountDown;
    if (SpeedMult == 0)
        AudioHelper::StopSample(deathBGMInstance);
    if (deathCountDown == -1 && lives > 0) {
        AudioHelper::StopSample(deathBGMInstance);
        dangerIndicator->Tint.a = 0;
    }
    if (SpeedMult == 0)
        deathCountDown = -1;
    for (int i = 0; i < SpeedMult; i++) {
        IScene::Update(deltaTime);
        // Check if we should create new enemy.
        ticks += deltaTime;
        if (enemyWaveData.empty()) {
            if (EnemyGroup->GetObjects().empty()) {
                // Win.
                Engine::EngineGame::GetInstance().ChangeScene("win");
            }
            continue;
        }
        auto current = enemyWaveData.front();
        if (ticks < std::get<1>(current))  //change
            continue;
        ticks -= std::get<1>(current);
        enemyWaveData.pop_front();
        std::random_device dev;
        std::mt19937 rng(dev());
        std::shuffle(laneNum.begin(), laneNum.end(), rng);
        std::uniform_int_distribution<std::mt19937::result_type> dist(1, 3);
        Enemy* enemy;
        for (int j = 0; j < std::get<2>(current); j++) {
            const Engine::Point SpawnCoordinate = Engine::Point(SpawnGridPointx * BlockSize + BlockSize / 2 + dist(rng) * 15, laneNum[j] * BlockSize + BlockSize / 2);
            switch (std::get<0>(current)) {
                case 1:
                    EnemyGroup->AddNewObject(enemy = new EnemyNormal(SpawnCoordinate.x, SpawnCoordinate.y));
                    break;
                case 2:
                    EnemyGroup->AddNewObject(enemy = new EnemySofa(SpawnCoordinate.x, SpawnCoordinate.y));
                    break;
                case 3:
                    EnemyGroup->AddNewObject(enemy = new EnemyStrong(SpawnCoordinate.x, SpawnCoordinate.y));
                    break;
                    // nTODO 2 (7/8): You need to modify 'resources/enemy1.txt', or 'resources/enemy2.txt' to spawn the 4th enemy.
                    //         The format is "[EnemyId] [TimeDelay] [LaneNum] [Repeat]".
                    // nTODO 2 (8/8): Enable the creation of the 4th enemy.
                case 4:
                    EnemyGroup->AddNewObject(enemy = new EnemyNerd(SpawnCoordinate.x, SpawnCoordinate.y));
                    break;
                default:
                    continue;
            }
            // Compensate the time lost.
            enemy->Update(ticks);
        }
    }
    if (preview) {
        preview->Position = Engine::EngineGame::GetInstance().GetMousePosition();
        // To keep responding when paused.
        preview->Update(deltaTime);
    }
}
void ScenePlay::Draw() const {
    UIMoney->Text = std::string("$") + std::to_string(this->money);
    UILives->Text = std::string("Life ") + std::to_string(lives);
    IScene::Draw();
}
void ScenePlay::OnMouseDown(int button, int mx, int my) {
    if ((button & 1) && !imgTarget->Visible && preview) {
        // Cancel turret construct.
        UIGroup->RemoveObject(preview->GetObjectIterator());
        preview = nullptr;
    }
    IScene::OnMouseDown(button, mx, my);
}
void ScenePlay::OnMouseMove(int mx, int my) {
    IScene::OnMouseMove(mx, my);
    const int x = mx / BlockSize;
    const int y = my / BlockSize;
    if (!preview || x < 0 || x >= MapWidth || y < 0 || y >= MapHeight) {
        imgTarget->Visible = false;
        return;
    }
    imgTarget->Visible = true;
    imgTarget->Position.x = x * BlockSize;
    imgTarget->Position.y = y * BlockSize;
}
void ScenePlay::OnMouseUp(int button, int mx, int my) {
    IScene::OnMouseUp(button, mx, my);
    if (!imgTarget->Visible)
        return;
    const int x = mx / BlockSize;
    const int y = my / BlockSize;
    if (button & 1) {
        if (mapState[y][x] != TILE_OCCUPIED) {
            if (!preview)
                return;
            // Check if valid.
            if (!CheckSpaceValid(x, y)) {
                Engine::Sprite* sprite;
                GroundEffectGroup->AddNewObject(sprite = new EffectDirty("play/target-invalid.png", 1, x * BlockSize + BlockSize / 2, y * BlockSize + BlockSize / 2));
                sprite->Rotation = 0;
                return;
            }
            // Purchase.
            EarnMoney(-preview->GetPrice());
            // Remove Preview.
            preview->GetObjectIterator()->first = false;
            UIGroup->RemoveObject(preview->GetObjectIterator());
            // Construct real turret.
            preview->Position.x = x * BlockSize + BlockSize / 2;
            preview->Position.y = y * BlockSize + BlockSize / 2;
            preview->Enabled = true;
            preview->Preview = false;
            preview->Tint = al_map_rgba(255, 255, 255, 255);
            TowerGroup->AddNewObject(preview);
            // To keep responding when paused.
            preview->Update(0);
            // Remove Preview.
            preview = nullptr;

            mapState[y][x] = TILE_OCCUPIED;
            OnMouseMove(mx, my);
        }
    }
}
void ScenePlay::OnKeyDown(int keyCode) {
    Engine::LOG(Engine::INFO) << keyCode;
    IScene::OnKeyDown(keyCode);
    // nTODO 4 (2/3): Set Tab as a code to active or de-active debug mode
    keyStrokes.push_back(keyCode);
    if (keyStrokes.size() > code.size())
        keyStrokes.pop_front();
    if (keyCode == ALLEGRO_KEY_TAB) {
        DebugMode = !DebugMode;
    } else {
        if (keyStrokes.size() == code.size() && DebugMode) {
            // nTODO 4 (3/3): Check whether the input sequence is correct
            bool Cheat = true;
            auto ic = code.begin();
            auto ik = keyStrokes.begin();
            for (; Cheat && ic != code.end() && ik != keyStrokes.end(); ic++, ik++)
                if (*ic != *ik) Cheat = false;
            if (Cheat) {
                EffectGroup->AddNewObject(new Plane());
                EarnMoney(10000);
                lives += 10;
            }
        }
    }
    if (keyCode == ALLEGRO_KEY_Q) {
        // Hotkey for TurretFire.
        UIBtnClicked(2);
    } else if (keyCode == ALLEGRO_KEY_W) {
        // Hotkey for TurretPlatelet.
        UIBtnClicked(1);
    } else if (keyCode == ALLEGRO_KEY_E) {
        // Hotkey for TurretFreeze.
        UIBtnClicked(0);
    }
    // nTODO 2 (5/8): Make the E key to create the 3th turret.
    else if (keyCode >= ALLEGRO_KEY_0 && keyCode <= ALLEGRO_KEY_9) {
        // Hotkey for Speed up.
        SpeedMult = keyCode - ALLEGRO_KEY_0;
    }
}
void ScenePlay::HitBy() {
    lives--;
    if (lives <= 0) {
        //lose
        Engine::EngineGame::GetInstance().ChangeScene("lose");
    }
}
int ScenePlay::GetMoney() const {
    return money;
}
void ScenePlay::EarnMoney(int money) {
    this->money += money;
    UIMoney->Text = std::string("$") + std::to_string(this->money);
}
void ScenePlay::ReadMap() {
    std::string filename = std::string("resources/map") + std::to_string(MapId) + ".txt";
    // Read map file.
    char c;
    std::vector<bool> mapData;
    std::ifstream fin(filename);
    while (fin >> c) {
        switch (c) {
            case '0':
                mapData.push_back(false);
                break;
            case '1':
                mapData.push_back(true);
                break;
            case '\n':
            case '\r':
                if (static_cast<int>(mapData.size()) / MapWidth != 0)
                    throw std::ios_base::failure("Map data is corrupted.");
                break;
            default:
                throw std::ios_base::failure("Map data is corrupted.");
        }
    }
    fin.close();
    // Validate map data.
    if (static_cast<int>(mapData.size()) != MapWidth * MapHeight)
        throw std::ios_base::failure("Map data is corrupted.");
    // Store map in 2d array.
    mapState = std::vector<std::vector<TileType>>(MapHeight, std::vector<TileType>(MapWidth));
    for (int i = 0; i < MapHeight; i++) {
        for (int j = 0; j < MapWidth; j++) {
            const int num = mapData[i * MapWidth + j];
            mapState[i][j] = num ? TILE_FLOOR : TILE_DIRT;
            if (num)
                TileMapGroup->AddNewObject(new Engine::Image("play/deep-pink.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
            else
                TileMapGroup->AddNewObject(new Engine::Image("play/pink.png", j * BlockSize, i * BlockSize, BlockSize, BlockSize));
        }
    }
}
void ScenePlay::ReadEnemyWave() {
    std::string filename = std::string("resources/enemy") + std::to_string(MapId) + ".txt";
    // Read enemy file.
    float type, wait, totallane, repeat;  //change
    enemyWaveData.clear();
    std::ifstream fin(filename);
    while (fin >> type && fin >> wait && fin >> totallane && fin >> repeat) {
        for (int i = 0; i < repeat; i++)
            enemyWaveData.emplace_back(type, wait, totallane);
    }
    fin.close();
}
void ScenePlay::ConstructUI() {
    // Background
    UIGroup->AddNewObject(new Engine::Image("play/sand.png", 0, 128 * MapHeight, 1536, 128));
    // Text
    //UIGroup->AddNewObject(new Engine::Label(std::string("Stage ") + std::to_string(MapId), "pirulen.ttf", 32, 1294, 0));
    UIGroup->AddNewObject(UIMoney = new Engine::Label(std::string("$") + std::to_string(money), "pirulen.ttf", 24, 1294, 128 * MapHeight));
    UIGroup->AddNewObject(UILives = new Engine::Label(std::string("Life ") + std::to_string(lives), "pirulen.ttf", 24, 1294, 128 * MapHeight + 30));

    ButtonTurret* btn;
    // Button 1 Turret Fire
    btn = new ButtonTurret("play/floor.png", "play/dirt.png",
                           Engine::Sprite("play/turret-3.png", 180, BlockSize * MapHeight, 0, 0, 0, 0), 170, 128 * MapHeight, TurretFire::Price);
    // Reference: Class Member Function Pointer and std::bind.
    btn->SetOnClickCallback(std::bind(&ScenePlay::UIBtnClicked, this, 2));
    UIGroup->AddNewControlObject(btn);

    // Button 2 Turret Platelet
    btn = new ButtonTurret("play/floor.png", "play/dirt.png",
                           Engine::Sprite("play/turret-2.png", 300, BlockSize * MapHeight, 0, 0, 0, 0), 290, 128 * MapHeight, TurretPlatelet::Price);
    btn->SetOnClickCallback(std::bind(&ScenePlay::UIBtnClicked, this, 1));
    UIGroup->AddNewControlObject(btn);
    // nTODO 2 (3/8): Create a button to support constructing the 3th tower.
    // Button 3 Turret Freeze
    btn = new ButtonTurret("play/floor.png", "play/dirt.png",
                           Engine::Sprite("play/turret-1.png", 420, BlockSize * MapHeight, 0, 0, 0, 0), 410, 128 * MapHeight, TurretFreeze::Price);
    btn->SetOnClickCallback(std::bind(&ScenePlay::UIBtnClicked, this, 0));
    UIGroup->AddNewControlObject(btn);

    int w = Engine::EngineGame::GetInstance().GetScreenSize().x;
    int h = Engine::EngineGame::GetInstance().GetScreenSize().y;
    int shift = 135 + 25;
    dangerIndicator = new Engine::Sprite("play/benjamin.png", w - shift, h - shift);
    dangerIndicator->Tint.a = 0;
    UIGroup->AddNewObject(dangerIndicator);
}

void ScenePlay::UIBtnClicked(int id) {
    if (preview) {
        UIGroup->RemoveObject(preview->GetObjectIterator());
        preview = nullptr;
    }
    if (id == 0 && money >= TurretFreeze::Price)
        preview = new TurretFreeze(0, 0);
    else if (id == 1 && money >= TurretPlatelet::Price)
        preview = new TurretPlatelet(0, 0);
    else if (id == 2 && money >= TurretFire::Price)
        preview = new TurretFire(0, 0);
    // nTODO 2 (4/8): On callback, create the 3th tower.
    if (!preview)
        return;
    preview->Position = Engine::EngineGame::GetInstance().GetMousePosition();
    preview->Tint = al_map_rgba(255, 255, 255, 200);
    preview->Enabled = false;
    preview->Preview = true;
    UIGroup->AddNewObject(preview);
    OnMouseMove(Engine::EngineGame::GetInstance().GetMousePosition().x, Engine::EngineGame::GetInstance().GetMousePosition().y);
}

bool ScenePlay::CheckSpaceValid(int x, int y) {
    if (x < 0 || x >= MapWidth || y < 0 || y >= MapHeight)
        return false;
    for (auto& it : EnemyGroup->GetObjects()) {
        Engine::Point pnt;
        pnt.x = floor(it->Position.x / BlockSize);
        pnt.y = floor(it->Position.y / BlockSize);
        if (pnt.x < 0) pnt.x = 0;
        if (pnt.x >= MapWidth) pnt.x = MapWidth - 1;
        if (pnt.y < 0) pnt.y = 0;
        if (pnt.y >= MapHeight) pnt.y = MapHeight - 1;
        if (pnt.x == x && pnt.y == y) {
            return false;
        }
    }
    return true;
}
