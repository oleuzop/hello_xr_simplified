// Copyright (c) 2017-2023, The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <string>
#include <locale>
#include <algorithm>
#include <stdarg.h>
#include <stddef.h>

#include <openxr/openxr_reflection.h>

// Macro to generate stringify functions for OpenXR enumerations based data provided in openxr_reflection.h
// clang-format off
#define ENUM_CASE_STR(name, val) case name: return #name;
#define MAKE_TO_STRING_FUNC(enumType)                  \
    inline const char* to_string(enumType e) {         \
        switch (e) {                                   \
            XR_LIST_ENUM_##enumType(ENUM_CASE_STR)     \
            default: return "Unknown " #enumType;      \
        }                                              \
    }
// clang-format on

MAKE_TO_STRING_FUNC(XrReferenceSpaceType);
MAKE_TO_STRING_FUNC(XrViewConfigurationType);
MAKE_TO_STRING_FUNC(XrEnvironmentBlendMode);
MAKE_TO_STRING_FUNC(XrSessionState);
MAKE_TO_STRING_FUNC(XrResult);
MAKE_TO_STRING_FUNC(XrFormFactor);

// The equivalent of C++17 std::size. A helper to get the dimension for an array.
template <typename T, size_t Size>
constexpr size_t ArraySize(const T (&/*unused*/)[Size]) noexcept {
    return Size;
}

#include "logger.h"
#include "check.h"
