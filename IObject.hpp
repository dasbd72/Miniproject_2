#ifndef IOBJECT_HPP
#define IOBJECT_HPP
#include <list>
#include <utility>

#include "Point.hpp"

namespace Engine {
	/// @brief The base interface class for objects that needs to be drawn or rendered.
	class IObject {
		friend class Group;
	protected:
		// The iterator of objects linked-list when added to scene.
		// Can make removing objects faster.
		// Reference: Iterator, which is also a Design Pattern when implementing.
		std::list<std::pair<bool, IObject*>>::iterator objectIterator{};
		/// @brief The interface cannot be instantiated directly, must be inherited.
		explicit IObject() = default;
		/// @brief @brief
		/// Construct an IObject.
		/// @param x X-coordinate.
		/// @param y Y-coordinate.
		/// @param w Width of the image, 0 indicates original size.
		/// @param h Height of the image, 0 indicates original size.
		/// @param anchorX The centerX of the object. (0, 0) means top-left, while (1, 0) means top-right.
		/// @param anchorY The centerY of the object. (0, 1) means bottom-left, while (1, 1) means bottom-right.
		explicit IObject(float x, float y, float w = 0, float h = 0, float anchorX = 0, float anchorY = 0);
	public:
		// Determines whether this object should be drawn and updated.
		bool Visible = true;
		// The object's position, center depends on Anchor.
		Point Position;
		// The object's size.
		Point Size;
		// The center of the object. (0, 0) means top-left, (1, 1) means bottom-right.
		Point Anchor;
		/// @brief The default virtual destructor to support polymorphism destruction.
		virtual ~IObject() = default;
		/// @brief Copy constructor does not add a new instance to scene, they are still the same object.
		IObject(const IObject& other) = default;
		/// @brief Copy assignment operator does not add a new instance to scene, they are still the same object.
		IObject& operator=(IObject const&) = default;
		/// @brief Retrieve the object iterator for later insertion.
		/// @return The object iterator.
		std::list<std::pair<bool, IObject*>>::iterator GetObjectIterator() const;
		/// @brief Draw to window display.
		/// This is called when the game should redraw the window.
		virtual void Draw() const;
		/// @brief Run game logic such as updating the world, checking for collision, and so on.
		/// This is called when the game should update its logic, usually 'fps' times per second.
		/// @param deltaTime Time elapsed since last update, can be used to calculate value changes.
		virtual void Update(float deltaTime);
	};
}
#endif // IOBJECT_HPP
