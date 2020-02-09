#pragma once

// Default C headers
#include <ctime>
#include <cmath>
#include <cstdio>
#include <cassert>
#include <cassert>
#include <cstdlib>
#include <cstdint>
#include <regex>
#include <fstream>
#include <sstream>

// Default C++ headers
#include <map>
#include <list>
#include <stack>
#include <array>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

// Default GIR headers
#include <Core/Type.hpp>
#include <Core/Math.hpp>
#include <Core/Logger.hpp>

#define SMALL_NUMBER (1.e-8f)
#define BIG_NUMBER (3.4e+38f)

#ifndef PI
#define PI (3.14159265359f)
#endif
#define INV_PI (0.31830988618f)
#define HALF_PI (1.57079632679f)

#define DEG2RAD (0.01745329251f)
#define RAD2DEG (57.2957795131f)

#ifdef GIR_WARN_UNUSED
#define GIR_UNUSED(_var_) gir::Logger::Warn("Unused variable {0}", #var);
#else
#define GIR_UNUSED(_var_) (void)var;
#endif

#define GIR_CHECK(_expr_, _msg_) gir::core::Check(_expr_, #_expr_, __FILE__, __LINE__, _msg_)

#ifndef NDEBUG
#define GIR_ASSERT(_expr_, _msg_) gir::core::Assert(_expr_, #_expr_, __FILE__, __LINE__, _msg_)
#else
#define GIR_ASSERT(_expr_, _msg_) /* Assertion availble only in debug mode */
#endif

namespace gir
{
    namespace core
    {
        /// Check if an expression is valid.
        /// @expr: the expression to check.
        /// @exprStr: the expected expression.
        /// @file: the file where the check was called.
        /// @line: the line where the check was called.
        inline void Check(bool expr, const char* exprStr, const char* file, int line, const char* msg)
        {
            if (!expr)
            {
                Logger::Error("Check failed: {0}, expected: \"{1}\".", msg, exprStr);
                Logger::Error("Source: {0}, line {1}.", file, line);
                exit(EXIT_FAILURE);
            }
        }

        /// Custom assert function.
        /// @expr: the expression to check.
        /// @exprStr: the expected expression.
        /// @file: the file where the assertion was raised.
        /// @line: the line where the assertion was raised.
        inline void Assert(bool expr, const char* exprStr, const char* file, int line, const char* msg)
        {
            if (!expr)
            {
                Logger::Error("Assertion failed: {0}, expected: \"{1}\".", msg, exprStr);
                Logger::Error("Source: {0}, line {1}.", file, line);
                exit(EXIT_FAILURE);
            }
        }
    } // namespace core
} // namespace gir