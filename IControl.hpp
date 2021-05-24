#ifndef ICONTROL_HPP
#define ICONTROL_HPP
#include <list>
#include <utility>

namespace Engine {
	/// @brief The base interface class for controls that needs to process event callbacks.
	
	class IControl {
		friend class Group;
	protected:
		// The iterator of controls linked-list when added to scene.
		// Can make removing controls faster.
		std::list<std::pair<bool, IControl*>>::iterator controlIterator{};
		/// @brief The interface cannot be instantiated directly, must be inherited.
		explicit IControl() = default;
	public:
		/// @brief The default virtual destructor to support polymorphism destruction.
		virtual ~IControl() = default;
		/// @brief Copy constructor does not add a new instance to scene, they are still the same object.
		IControl(const IControl& other) = default;
		/// @brief Copy assignment operator does not add a new instance to scene, they are still the same object.
		IControl& operator=(IControl const&) = default;
		/// @brief Delegated from scene when keyboard key down.
		/// @param keyCode The keycode of pressed key.
		virtual void OnKeyDown(int keyCode);
		/// @brief Delegated from scene when keyboard key up.
		/// @param keyCode The keycode of released key.
		virtual void OnKeyUp(int keyCode);
		/// @brief Delegated from scene when mouse button down.
		/// @param button The button pressed.
		/// @param mx Mouse x coordinate in window space.
		/// @param my Mouse y coordinate in window space.
		virtual void OnMouseDown(int button, int mx, int my);
		/// @brief Delegated from scene when mouse button up.
		/// @param button The button released.
		/// @param mx Mouse x coordinate in window space.
		/// @param my Mouse y coordinate in window space.
		virtual void OnMouseUp(int button, int mx, int my);
		/// @brief Delegated from scene when mouse move.
		/// @param mx Mouse x coordinate in window space.
		/// @param my Mouse y coordinate in window space.
		virtual void OnMouseMove(int mx, int my);
		/// @brief Delegated from scene when mouse scroll.
		
		/// @param mx Mouse x coordinate in window space.
		/// @param my Mouse y coordinate in window space.
		/// @param delta Mouse z scroll delta value.
		virtual void OnMouseScroll(int mx, int my, int delta);
	};
}
#endif // ICONTROL_HPP
