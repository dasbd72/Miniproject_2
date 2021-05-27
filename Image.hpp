#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <allegro5/bitmap.h>

#include <memory>
#include <string>

#include "IObject.hpp"

namespace Engine {
/// @brief A simple static image object.
class Image : public IObject {
   public:
    // Smart pointer to bitmap.
    std::shared_ptr<ALLEGRO_BITMAP> bmp;
    /// @brief Construct a image object.
    /// @param img The image path in 'resources/images/'
    /// @param x X-coordinate.
    /// @param y Y-coordinate.
    /// @param w Width of the image, 0 indicates original size.
    /// @param h Height of the image, 0 indicates original size.
    /// @param anchorX The centerX of the object. (0, 0) means top-left, while (1, 0) means top-right.
    /// @param anchorY The centerY of the object. (0, 1) means bottom-left, while (1, 1) means bottom-right.
    explicit Image(std::string img, float x, float y, float w = 0, float h = 0, float anchorX = 0, float anchorY = 0);
    /// @brief Draw the loaded image.
    void Draw() const override;
    /// @brief Return bitmap width.
    /// @return Width of the original or scaled bitmap.
    int GetBitmapWidth() const;
    /// @brief Return bitmap height.
    /// @return Height of the original or scaled bitmap.
    int GetBitmapHeight() const;
};
}  // namespace Engine
#endif  // IMAGE_HPP
