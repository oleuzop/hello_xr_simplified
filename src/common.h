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

void MonoPrint(const char* format, ...);

[[noreturn]] inline void Throw(std::string failureMessage, const char* originator = nullptr) {
    MonoPrint("Message: %s", failureMessage);
    if (originator != nullptr) {
        MonoPrint("Origin: %s", originator);
    }
}

#define CHECK(exp)                                      \
    {                                                   \
        if (!(exp)) {                                   \
            Throw("Check failed", #exp);                \
        }                                               \
    }
#define CHECK_MSG(exp, msg)                  \
    {                                        \
        if (!(exp)) {                        \
            Throw(msg, #exp);                \
        }                                    \
    }

[[noreturn]] inline void ThrowXrResult(XrResult res, const char* originator = nullptr) {
    Throw(("XrResult = " + std::to_string(res)).c_str(), originator);
}

inline XrResult CheckXrResult(XrResult res, const char* originator = nullptr) {
    if (XR_FAILED(res)) {
        ThrowXrResult(res, originator);
    }
    return res;
}

#define THROW_XR(xr, cmd) ThrowXrResult(xr, #cmd);
#define CHECK_XRCMD(cmd) CheckXrResult(cmd, #cmd);
#define CHECK_XRRESULT(res, cmdStr) CheckXrResult(res, cmdStr);

[[noreturn]] inline void ThrowHResult(HRESULT hr, const char* originator = nullptr) {
    Throw(("HRESULT failure = " + std::to_string(hr)).c_str(), originator);
}

inline HRESULT CheckHResult(HRESULT hr, const char* originator = nullptr) {
    if (FAILED(hr)) {
        ThrowHResult(hr, originator);
    }
    return hr;
}

#define THROW_HR(hr, cmd) ThrowHResult(hr, #cmd);
#define CHECK_HRCMD(cmd) CheckHResult(cmd, #cmd);
#define CHECK_HRESULT(res, cmdStr) CheckHResult(res, cmdStr);

