#include "TrussC.h"
#include "tcPlatform.h"
#include "tc/platform/c_exports.h"
#include <string>

extern "C" {

    float trussc_platform_getDisplayScaleFactor() {
        return trussc::getDisplayScaleFactor();
    }

    const char* trussc_platform_getExecutableDir() {
        static std::string dir;
        dir = trussc::getExecutableDir();
        return dir.c_str();
    }

    int trussc_platform_saveScreenshot(const char* path) {
        return trussc::saveScreenshot(std::filesystem::path(path));
    }

    void trussc_platform_bringWindowToFront(){
        trussc::bringWindowToFront();
    }

    void trussc_platform_setWindowSize(int width, int height){
        trussc::setWindowSizeLogical(width, height);
    }

    int trussc_platform_captureWindow(void* outPixels) {
        if (!outPixels) return 0;
        trussc::Pixels* p = reinterpret_cast<trussc::Pixels*>(outPixels);
        bool ok = trussc::captureWindow(*p);
        return ok ? 1 : 0;
    }

    void trussc_setup() {
        trussc::setup();
    }

    void trussc_cleanup() {
        trussc::cleanup();
    }

    void trussc_internal_resizeSgl(int newMaxVertices, int newMaxCommands) {
        trussc::internal::resizeSgl(newMaxVertices, newMaxCommands);
    }

    void trussc_clear(float r, float g, float b, float a) {
        trussc::clear(r, g, b, a);
    }

} // extern "C"
