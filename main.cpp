// [main.cpp]
// this template is provided for the 2D tower defense game.
// Program entry point.
// Returns program exit code.
#include "EngineGame.hpp"
#include "LOG.hpp"
#include "SceneLose.hpp"
#include "ScenePlay.hpp"
#include "SceneSetting.hpp"
#include "SceneStageSelect.hpp"
#include "SceneStart.hpp"
#include "SceneWin.hpp"

int main(int argc, char** argv) {
    Engine::LOG::SetConfig(true);
    Engine::EngineGame& game = Engine::EngineGame::GetInstance();
    // nTODO 1 (1/3): Add a New Scene here
    game.AddNewScene("stage-select", new SceneStageSelect());
    game.AddNewScene("play", new ScenePlay());
    game.AddNewScene("lose", new SceneLose());
    game.AddNewScene("win", new SceneWin());
    game.AddNewScene("setting", new SceneSetting());
    game.AddNewScene("start_scene", new StartScene());

    game.Start("start_scene", 60, 1536, 896);
    return 0;
}
