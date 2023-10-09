// Copyright (c) 2017-2023, The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#pragma once


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
