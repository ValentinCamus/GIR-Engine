#pragma once

#include <spdlog/spdlog.h>

namespace gir
{
    enum class ELogLevel
    {
        Debug = SPDLOG_LEVEL_DEBUG,
        Info = SPDLOG_LEVEL_INFO,
        Warn = SPDLOG_LEVEL_WARN,
        Error = SPDLOG_LEVEL_ERROR,
        Silent = SPDLOG_LEVEL_OFF,
    };

    class Logger
    {
    public:
        /// Log a debug message.
        /// @fmt : The log message.
        template<typename T>
        static inline void Debug(const T& message)
        {
            spdlog::debug(message);
        }

        /// Log a info message.
        /// @fmt : The log message
        template<typename T>
        static inline void Info(const T& message)
        {
            spdlog::info(message);
        }

        /// Log a warning message.
        /// @fmt : The log message.
        template<typename T>
        static inline void Warn(const T& message)
        {
            spdlog::warn(message);
        }

        /// Log a error message.
        /// @fmt : The log message.
        template<typename T>
        static inline void Error(const T& message)
        {
            spdlog::error(message);
        }

        /// Log a debug message.
        /// @fmt : The format of the log message.
        ///        The format uses "{<index>}" to make a reference to the argument at the index <index>.
        ///        The argument index start with 0.
        /// @args : A list of arguments, can be empty.
        template<typename ... Args>
        static inline void Debug(const char * fmt, const Args&... args)
        {
            spdlog::debug(fmt, args...);
        }

        /// Log a info message.
        /// @fmt : The format of the log message.
        ///        The format uses "{<index>}" to make a reference to the argument at the index <index>.
        ///        The argument index start with 0.
        /// @args : A list of arguments, can be empty.
        template<typename ... Args>
        static inline void Info(const char * fmt, const Args&... args)
        {
            spdlog::info(fmt, args...);
        }

        /// Log a warning message.
        /// @fmt : The format of the log message.
        ///        The format uses "{<index>}" to make a reference to the argument at the index <index>.
        ///        The argument index start with 0.
        /// @args : A list of arguments, can be empty.
        template<typename ... Args>
        static inline void Warn(const char * fmt, const Args&... args)
        {
            spdlog::warn(fmt, args...);
        }

        /// Log a error message.
        /// @fmt : The format of the log message.
        ///        The format uses "{<index>}" to make a reference to the argument at the index <index>.
        ///        The argument index start with 0.
        /// @args : A list of arguments, can be empty.
        template<typename ... Args>
        static inline void Error(const char * fmt, const Args&... args)
        {
            spdlog::error(fmt, args...);
        }

        static inline void SetLogLevel(ELogLevel lvl)
        {
            auto format = static_cast<spdlog::level::level_enum>(lvl);
            spdlog::set_level(format);
        }
    };
}
