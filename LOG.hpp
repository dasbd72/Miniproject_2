#ifndef LOG_HPP
#define LOG_HPP
#include <fstream>
#include <iostream>

namespace Engine {
// Log types that will be formatted in front of the line.
enum LogType {
    VERBOSE,
    DEBUGGING,
    INFO,
    WARN,
    ERROR
};

/// @brief Helper log class for quick logging to console and file. Can be used like std::cout.
class LOG final {
   private:
    // Determine if global log is enabled.
    static bool Enabled;
    // Determine whether should log verbose messages or not.
    static bool LogVerbose;
    // The file path of the log file.
    static const char* FilePath;
    /// @brief Get the label from log type.
    /// @param type Log type of a log instance.
    /// @return Returns the string label of the type.
    static const char* getLabel(LogType type);
    // File stream to write to.
    std::ofstream ofs;
    // Determines if log is enabled.
    bool enabled;
    /// @brief Check should we log the message.
    /// @return Determines whether the messages should be logged.
    bool canLog() const;

   public:
    // Determines the prefix label.
    LogType type;
    /// @brief Start a log chain with certain type.
    /// @param type The type of this log chain, default is DEBUGGING.
    explicit LOG(LogType type = DEBUGGING);
    /// @brief Add new line and close file.
    ~LOG();
    /// @brief Support logging chain that can be used in the same way as std::cout.
    template <class T>
    LOG& operator<<(const T& msg) {
        if (canLog()) {
            std::cout << msg;
            ofs << msg;
        }
        return *this;
    }
    /// @brief Set global configuration.
    /// @param enabled Determine if global log is enabled.
    /// @param logVerbose Determine whether should log verbose messages or not.
    /// @param filePath The file path of the log file.
    static void SetConfig(bool enabled = false, bool logVerbose = false, const char* filePath = "log.txt");
};
}  // namespace Engine
#endif  // LOGGER_HPP
