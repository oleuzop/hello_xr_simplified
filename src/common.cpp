// Copyright (c) 2017-2023, The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <cstdarg>
#include <cstdio>

void MonoPrint(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf("\n");
}