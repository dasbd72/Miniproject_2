#ifndef GROUP_HPP
#define GROUP_HPP
#include <list>
#include <utility>

#include "IControl.hpp"
#include "IObject.hpp"

namespace Engine {
	/// @brief A ControlObject Group that can contain other objects or controls.
	class Group: public IObject, public IControl {
	protected:
		// Stores all object pointers in the scene.
		// The first boolean indicates whether the scene should delete it.
		std::list<std::pair<bool, IObject*>> objects;
		// Stores all control pointers in the scene.
		// The first boolean indicates whether the scene should delete it.
		std::list<std::pair<bool, IControl*>> controls;
		// Note: Using linked-list and inline-new might cause some serious cache misses,
		//       however this implementation brings us more convenience than the impact
		//       on performance. Trying to deal with cache misses requires complicated code,
		//       so we'll just ignore it for simplicity.
		/// @brief Add Object to scene.
		/// @param shouldDelete Indicates whether the scene handle the Object deletion for you.
		/// @param obj The Object to add.
		void addObject(bool shouldDelete, IObject* obj);
		/// @brief Add Control to scene.
		/// @param shouldDelete Indicates whether the scene handle the Control deletion for you.
		/// @param ctrl The Control to add.
		void addControl(bool shouldDelete, IControl* ctrl);
		/// @brief Insert Object to scene before the iterator.
		/// @param shouldDelete Indicates whether the scene handle the deletion for you.
		/// @param obj The Object to insert.
		/// @param it The iterator that the object should insert before.
		void insertObject(bool shouldDelete, IObject* obj, std::list<std::pair<bool, IObject*>>::iterator it);
	public:
		/// @brief Create an empty group.
		explicit Group() = default;
		/// @brief Copy constructor is deleted, no copying allowed.
		Group(Group const&) = delete;
		/// @brief Copy assignment operator is deleted, no copy assignment allowed.
		Group& operator=(Group const&) = delete;
		/// @brief The default virtual destructor to support polymorphism destruction.
		virtual ~Group();
		/// @brief Remove all children (objects and controls).
		void Clear();
		/// @brief Run game logic such as updating the world, checking for collision, and so on.
		/// This is called when the game should update its logic, usually 'fps' times per second.
		/// Delegate the update event to all visible objects.
		/// @param deltaTime Time elapsed since last update, can be used to calculate value changes.
		void Update(float deltaTime) override;
		/// @brief Draw to window display.
		/// This is called when the game should redraw the window.
		/// Delegate the draw event to all visible objects.
		void Draw() const override;
		/// @brief Delegate the key down event to all controls.
		/// @param keyCode The keycode of pressed key.
		void OnKeyDown(int keyCode) override;
		/// @brief Delegate the key up event to all controls.
		/// @param keyCode The keycode of released key.
		void OnKeyUp(int keyCode) override;
		/// @brief Delegate the mouse key down event to all controls.
		/// @param button The button pressed.
		/// @param mx Mouse x coordinate in window space.
		/// @param my Mouse y coordinate in window space.
		void OnMouseDown(int button, int mx, int my) override;
		/// @brief Delegate the mouse key up event to all controls.
		/// @param button The button released.
		/// @param mx Mouse x coordinate in window space.
		/// @param my Mouse y coordinate in window space.
		void OnMouseUp(int button, int mx, int my) override;
		/// @brief Delegate the mouse move event to all controls.
		/// @param mx Mouse x coordinate in window space.
		/// @param my Mouse y coordinate in window space.
		void OnMouseMove(int mx, int my) override;
		/// @brief Delegate the mouse scroll event to all controls.
		/// @param mx Mouse x coordinate in window space.
		/// @param my Mouse y coordinate in window space.
		/// @param delta Mouse z scroll delta value.
		void OnMouseScroll(int mx, int my, int delta) override;
		/// @brief Remove the Object from this scene.
		/// @param it The iterator of the Object.
		void RemoveObject(std::list<std::pair<bool, IObject*>>::iterator it);
		/// @brief Remove the Control from this scene.
		/// @param it The iterator of the Control.
		void RemoveControl(std::list<std::pair<bool, IControl*>>::iterator it);
		/// @brief Remove the ControlObject from this scene.
		/// @param ctrlIt The iterator of the Control.
		/// @param objIt The iterator of the Object.
		void RemoveControlObject(std::list<std::pair<bool, IControl*>>::iterator ctrlIt, std::list<std::pair<bool, IObject*>>::iterator objIt);
		/// @brief Add Object to scene.
		/// Use inline-new when adding Object in order to support polymorphism,
		/// The added objects will be deleted by Scene at remove or terminate.
		/// @param obj The Object to add.
		void AddNewObject(IObject* obj);
		/// @brief Insert Object to scene before the iterator.
		/// Use inline-new when adding Object in order to support polymorphism,
		/// The added objects will be deleted by Scene at remove or terminate.
		/// @param obj The Object to insert.
		/// @param it The iterator that the object should insert before.
		void InsertNewObject(IObject* obj, std::list<std::pair<bool, IObject*>>::iterator it);
		/// @brief Add Control to scene.
		/// Use inline-new when adding Control in order to support polymorphism,
		/// The added controls will be deleted by Scene at remove or terminate.
		/// @param ctrl The Control to add.
		void AddNewControl(IControl* ctrl);
		/// @brief Add ControlObject to scene.
		/// Use inline-new when adding ControlObject in order to support polymorphism,
		/// ControlObject means classes that inherit both Control and Object. (e.g. buttons)
		/// @param ctrl The ControlObject to add.
		void AddNewControlObject(IControl* ctrl);
		/// @brief Add Object to scene.
		/// Use reference when adding Object. Make sure it won't be deconstructed due to out-of-scope.
		/// The added objects will not be deleted by Scene at remove or terminate.
		/// @param obj The Object to add.
		void AddRefObject(IObject& obj);
		/// @brief Insert Object to scene before the iterator.
		/// Use reference when adding Object. Make sure it won't be deconstructed due to out-of-scope.
		/// The added objects will not be deleted by Scene at remove or terminate.
		/// @param obj The Object to insert.
		/// @param it The iterator that the object should insert before.
		void InsertRefObject(IObject& obj, std::list<std::pair<bool, IObject*>>::iterator it);
		/// @brief Add Control to scene.
		/// Use reference when adding Control. Make sure it won't be deconstructed due to out-of-scope.
		/// The added controls will not be deleted by Scene at remove or terminate.
		/// @param ctrl The Control to add.
		void AddRefControl(IControl& ctrl);
		/// @brief Add ControlObject to scene.
		/// Use reference when adding ControlObject. Make sure it won't be deconstructed due to out-of-scope.
		/// The added ControlObjects will not be deleted by Scene at remove or terminate.
		/// @param ctrl The ControlObject to add.
		void AddRefControlObject(IControl& ctrl);
		/// @brief Get all objects.
		/// @return A linked-list of all objects contained.
		std::list<IObject*> GetObjects();
		/// @brief Get all controls.
		/// @return A linked-list of all controls contained.
		std::list<IControl*> GetControls();
	};
}
#endif // GROUP_HPP
