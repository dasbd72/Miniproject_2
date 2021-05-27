#ifndef ALLEGRO5EXCEPTION_HPP
#define ALLEGRO5EXCEPTION_HPP
#include <stdexcept>
#include <string>

namespace Engine {
/// @brief Exception class dedicated to Allegro5 library's exception.
class Allegro5Exception final : public std::runtime_error {
   public:
    /// @brief Allegro5 error with char array message.
    /// @param message The error message.
    explicit Allegro5Exception(char const* const message) noexcept;
    /// @brief Allegro5 error with std::string message.
    /// @param message The error message.
    explicit Allegro5Exception(const std::string& message) noexcept;
};
}  // namespace Engine
#endif  // ALLEGRO5EXCEPTION_HPP
