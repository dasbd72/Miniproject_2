#ifndef ISCENE_HPP
#define ISCENE_HPP

#include "Group.hpp"

namespace Engine {
    /// @brief This class should be inherited whenever you want to define a new scene.
    /// Responsible for delegating draw, update, events to the objects and controls in scene.
    /// Acts like a prototype, so all initialize and terminate shouldn't be put in constructor or destructor.
    class IScene: public Group {
    protected:
        /// @brief The interface cannot be instantiated directly, must be inherited.
        explicit IScene() = default;
    public:
        /// @brief Copy constructor is deleted, no copying allowed.
        IScene(IScene const&) = delete;
        /// @brief Copy assignment operator is deleted, no copy assignment allowed.
        IScene& operator=(IScene const&) = delete;
        /// @brief The default virtual destructor to support polymorphism destruction.
        virtual ~IScene() = default;
        /// @brief Put all initialize code here instead of constructor to make change scene more simple.
        virtual void Initialize() = 0;
        /// @brief Put all terminate code here instead of destructor to make change scene more simple.
        virtual void Terminate();
        /// @brief Draw to window display.
        /// This is called when the game should redraw the window.
        /// Delegate the draw event to all visible objects.
        void Draw() const override;
    };
}
#endif // ISCENE_HPP
