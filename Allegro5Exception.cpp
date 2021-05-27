#include "Allegro5Exception.hpp"

#include <stdexcept>

namespace Engine {
Allegro5Exception::Allegro5Exception(char const* const message) noexcept : std::runtime_error(message) {}
Allegro5Exception::Allegro5Exception(const std::string& message) noexcept : std::runtime_error(message.c_str()) {}
}  // namespace Engine
