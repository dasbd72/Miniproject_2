#ifndef SPRITE_HPP
#define SPRITE_HPP
#include <allegro5/color.h>
#include <string>

#include "Image.hpp"
#include "Point.hpp"

namespace Engine {
	/// @brief Image that supports rotation, velocity, tint, and collision radius.
	class Sprite : public Image {
	public:
		// Rotation angle in radians.
		float Rotation;
		// Pixel in seconds.
		Point Velocity;
		// Color tint.
		ALLEGRO_COLOR Tint;
		// Assume a circle is a good approximation of the sprite's boundary.
		float CollisionRadius = 0;
		/// @brief Construct a sprite (object).
		/// @param img The image path in 'resources/images/'
		/// @param x X-coordinate.
		/// @param y Y-coordinate.
		/// @param w Width of the image, 0 indicates original size.
		/// @param h Height of the image, 0 indicates original size.
		/// @param anchorX The centerX of the object. (0, 0) means top-left, while (1, 0) means top-right.
		/// @param anchorY The centerY of the object. (0, 1) means bottom-left, while (1, 1) means bottom-right.
		/// @param rotation Rotation in radians.
		/// @param vx X-Velocity.
		/// @param vy Y-Velocity.
		/// @param r Color tint red value.
		/// @param g Color tint green value.
		/// @param b Color tint blue value.
		/// @param a Color tint alpha value.
		explicit Sprite(std::string img, float x, float y, float w = 0, float h = 0, float anchorX = 0.5f, float anchorY = 0.5f,
			float rotation = 0, float vx = 0, float vy = 0, unsigned char r = 255, unsigned char g = 255, unsigned char b = 255, unsigned char a = 255);
		/// @brief Draw to window display.
		/// This is called when the game should redraw the window.
		void Draw() const override;
		/// @brief Run game logic such as updating the world, checking for collision, and so on.
		/// This is called when the game should update its logic, usually 'fps' times per second.
		/// @param deltaTime Time elapsed since last update, can be used to calculate value changes.
		void Update(float deltaTime) override;
	};
}
#endif // SPRITE_HPP

