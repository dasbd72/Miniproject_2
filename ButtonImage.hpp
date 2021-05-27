#ifndef IMAGEBUTTON_HPP
#define IMAGEBUTTON_HPP
#include <allegro5/bitmap.h>

#include <functional>
#include <memory>
#include <string>

#include "IControl.hpp"
#include "Image.hpp"

namespace Engine {
/// @brief A clickable button, changes image when mouse move.

class ButtonImage : public Image, public IControl {
   protected:
    // Determines whether mouse is in the button.
    bool mouseIn = false;
    // The smart pointer that points to bitmap for mouse-out display.
    std::shared_ptr<ALLEGRO_BITMAP> imgOut;
    // The smart pointer that points to bitmap for mouse-in display.
    std::shared_ptr<ALLEGRO_BITMAP> imgIn;
    // The callback function to call when button clicked.
    std::function<void()> OnClickCallback;

   public:
    // Whether the button can be pressed.
    bool Enabled = true;
    /// @brief Construct a image object.
    /// @param img The mouse-out image path in 'resources/images/'
    /// @param imgIn The mouse-in image path in 'resources/images/'
    /// @param x X-coordinate.
    /// @param y >Y-coordinate.
    /// @param w Width of the image, 0 indicates original size.
    /// @param h Height of the image, 0 indicates original size.
    /// @param anchorX The centerX of the object. (0, 0) means top-left, while (1, 0) means top-right.
    /// @param anchorY The centerY of the object. (0, 1) means bottom-left, while (1, 1) means bottom-right.
    explicit ButtonImage(std::string img, std::string imgIn, float x, float y, float w = 0, float h = 0, float anchorX = 0, float anchorY = 0);
    /// @brief the callback function when clicked.

    /// @param onClickCallback
    void SetOnClickCallback(std::function<void(void)> onClickCallback);
    /// @brief Delegated from scene when mouse button down.

    /// @param button The button pressed.
    /// @param mx Mouse x coordinate in window space.
    /// @param my Mouse y coordinate in window space.
    void OnMouseDown(int button, int mx, int my) override;
    /// @brief Delegated from scene when mouse move.

    /// @param mx Mouse x coordinate in window space.
    /// @param my Mouse y coordinate in window space.
    void OnMouseMove(int mx, int my) override;
};
}  // namespace Engine
#endif  // IMAGEBUTTON_HPP
