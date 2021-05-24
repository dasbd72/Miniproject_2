#ifndef LABEL_HPP
#define LABEL_HPP
#include <allegro5/allegro_font.h>
#include <allegro5/color.h>
#include <memory>
#include <string>

#include "IObject.hpp"

namespace Engine {
    /// @brief A simple static text object.
    class Label : public IObject {
    protected:
        // Smart pointer to font.
        std::shared_ptr<ALLEGRO_FONT> font;
    public:
        // Text to draw.
        std::string Text;
        // Text's color.
        ALLEGRO_COLOR Color;
        /// @brief Construct a label object.
        /// @param text Text to draw.
        /// @param font Font to draw in.
        /// @param fontSize Text's font size.
        /// @param x X-coordinate.
        /// @param y Y-coordinate.
        /// @param r Color's red value.
        /// @param g Color's green value.
        /// @param b Color's blue value.
        /// @param a Color's alpha value.
        /// @param anchorX The centerX of the object. (0, 0) means top-left, while (1, 0) means top-right.
        /// @param anchorY The centerY of the object. (0, 1) means bottom-left, while (1, 1) means bottom-right.
        explicit Label(const std::string& text, const std::string& font, int fontSize, float x, float y, unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255, float anchorX = 0, float anchorY = 0);
        /// @brief Draw text with loaded font.
        void Draw() const override;
        /// @brief Return text width.
        /// @return Width of the text.
        int GetTextWidth() const;
        /// @brief Return text height.
        /// @return Height of the text.
        int GetTextHeight() const;
    };
}

#endif // LABEL_HPP
