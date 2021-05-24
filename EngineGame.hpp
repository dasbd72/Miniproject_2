#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP
#include <allegro5/allegro.h>
#include <string>
#include <unordered_map>

#include "Point.hpp"

/// @brief All general classes are under this namespace for clarity.
namespace Engine {
    class IScene;
    /// @brief The one and only EngineGame for the entire program. Responsible for low-level initialization and window events.
    class EngineGame final {
    private:
        // Allegro5 settings, frames per second, screen width, screen height, maximum simultaneous audio samples.
        int fps{}, screenW{}, screenH{}, reserveSamples{};
        // Determines whether to free memory between scenes.
        bool freeMemoryOnSceneChanged{};
        // Max delta time for update multiplier. If delta time exceeds this threshold, lag occurs.
        float deltaTimeThreshold{};
        // All scenes are stored in hash table for easy access.
        // Reference: Data Structure - Hash table
        std::unordered_map<std::string, IScene*> scenes;
        // The active scene that occupies the game's update, draw and various events.
        IScene* activeScene{};
        // Allegro5 display for window creation.
        ALLEGRO_DISPLAY* display{};
        // Allegro5 event queue.
        ALLEGRO_EVENT_QUEUE* event_queue{};
        // Allegro5 timer to inject update & draw event into the event queue.
        ALLEGRO_TIMER* update_timer{};
        // The window's title text.
        const char* title{};
        // The window's icon.
        const char* icon{};
        // The scene to change to at next update.
        std::string nextScene{};

        /// @brief Initialize allegro5 library. Creates game window & event queue,
        /// install peripherals and initialize add-ons.
        
        void initAllegro5();
        /// @brief Process events inside the event queue using an infinity loop,
        /// exit when close button clicked.
        void startEventLoop();
        /// @brief Delegate the update event to the active scene.
        /// @param deltaTime Time elapsed since last update, can be used to calculate value changes.
        void update(float deltaTime);
        /// @brief Delegate the draw event to the active scene.
        void draw() const;
        /// @brief Release Allegro5 resources, and free all allocated scenes.
        void destroy();
        /// @brief Private constructor since this class is a Singleton.
        /// Note: Singleton is a class that will only be instantiated once (single instance).
        /// Reference: Design Patterns - Singleton.
        explicit EngineGame() = default;
        /// @brief Change to another scene. Must return immediately and stop using anything initialized in
        /// the scene. Since this call destroys everything initialized.
        /// @param name The name of the scene you want to change to.
        void changeScene(const std::string& name);
    public:
        // Note: We'll ignore C++11's move constructor, move assignment operator in this project for simplicity.
        /// @brief Copy constructor is deleted, no copying allowed.
        
        EngineGame(EngineGame const&) = delete;
        /// @brief Copy assignment operator is deleted, no copy assignment allowed.
        
        EngineGame& operator=(EngineGame const&) = delete;
        /// @brief Start the game loop until exit, scenes should be added before starting.
        /// @param firstSceneName The scene name of the first scene of the game.
        /// @param fps The target frame per seconds of the game.
        /// @param screenW Window screen width.
        /// @param screenH Window screen height.
        /// @param reserveSamples Maximum simultaneous audio samples.
        /// @param title Window's title text.
        /// @param icon Window's icon image path.
        /// @param freeMemoryOnSceneChanged Determines whether to free memory between scenes.
        void Start(const std::string& firstSceneName, int fps = 60, int screenW = 800, int screenH = 600, int reserveSamples = 1000,
                   const char* title = "Tower Defense (I2P(II)_2020 Mini Project 2))",
                   const char* icon = "icon.png", bool freeMemoryOnSceneChanged = false,
                   float deltaTimeThreshold = 0.05);
        /// @brief Add a new scene to the game. Should only be called once for each scene.
        /// Use inline-new when adding scene in order to support polymorphism,
        /// The added scenes will be deleted by EngineGame at game end.
        /// @param name The unique name of your scene for later access.
        /// @param scene The pointer to the scene you want to add.
        void AddNewScene(const std::string& name, IScene* scene);
        /// @brief Change to another scene. The scene will be changed at next update.
        /// @param name The name of the scene you want to change to.
        void ChangeScene(const std::string& name);
        /// @brief Get the pointer of the active scene.
        /// @return Pointer to active scene.
        IScene* GetActiveScene() const;
        /// @brief Get scene by name.
        /// @param name The scene's name.
        /// @return Pointer to scene.
        IScene* GetScene(const std::string& name);
        /// @brief Get screen size.
        /// @return Screen size.
        Point GetScreenSize() const;
        /// @brief Get screen width.
        /// @return Screen width.
        int GetScreenWidth() const;
        /// @brief Get screen height.
        /// @return Screen height.
        int GetScreenHeight() const;
        /// @brief Get mouse position.
        /// @return Get mouse position.
        Point GetMousePosition() const;
        /// @brief Get key state.
        /// @return Returns whether key is down or not.
        bool IsKeyDown(int keyCode) const;
        /// @brief Typical function to retrieve Singleton instance and supports lazy initialization.
        /// @return The Singleton instance of EngineGame.
        static EngineGame& GetInstance();
    };
}
#endif // GAMEENGINE_HPP
