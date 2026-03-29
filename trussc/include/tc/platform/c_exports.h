#pragma once

#include <cstddef>

// Portable C export macro: ensures symbols are exported on macOS (visibility)
#if defined(_WIN32) || defined(_WIN64)
#  ifdef TRUSSC_EXPORTS
#    define TRUSSC_C_API extern "C" __declspec(dllexport)
#  else
#    define TRUSSC_C_API extern "C" __declspec(dllimport)
#  endif
#else
#  define TRUSSC_C_API extern "C" __attribute__((visibility("default")))
#endif

// Platform wrappers
TRUSSC_C_API float trussc_platform_getDisplayScaleFactor();
TRUSSC_C_API const char* trussc_platform_getExecutableDir();
TRUSSC_C_API int trussc_platform_saveScreenshot(const char* path);
TRUSSC_C_API void trussc_platform_setWindowSize(int width, int height);
TRUSSC_C_API int trussc_platform_captureWindow(void* outPixels);

// Core lifecycle / internal
TRUSSC_C_API void trussc_setup();
TRUSSC_C_API void trussc_cleanup();
TRUSSC_C_API void trussc_internal_resizeSgl(int newMaxVertices, int newMaxCommands);
// Clear screen wrapper
TRUSSC_C_API void trussc_clear(float r, float g, float b, float a);

