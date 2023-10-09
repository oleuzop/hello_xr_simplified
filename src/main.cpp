#include "pch.h"
#include "common.h"
#include "graphicsplugin.h"
#include "openxr_program.h"

// Favor the high performance NVIDIA or AMD GPUs
extern "C" {
// http://developer.download.nvidia.com/devzone/devcenter/gamegraphics/files/OptimusRenderingPolicies.pdf
__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
// https://gpuopen.com/learn/amdpowerxpressrequesthighperformance/
__declspec(dllexport) DWORD AmdPowerXpressRequestHighPerformance = 0x00000001;
}

int main(int argc, char* argv[]) {
    try {

        // Spawn a thread to wait for a keypress
        bool quitKeyPressed = false;
        bool requestRestart = false;

        do {
            // Create graphics API implementation.
            std::shared_ptr<IGraphicsPlugin> graphicsPlugin = CreateGraphicsPlugin();

            // Initialize the OpenXR program.
            std::shared_ptr<IOpenXrProgram> program = CreateOpenXrProgram(graphicsPlugin);

            program->CreateInstance();
            program->InitializeSystem();

            program->InitializeDevice();
            program->InitializeSession();
            program->CreateSwapchains();

            while (!quitKeyPressed) {
                bool exitRenderLoop = false;
                program->PollEvents(&exitRenderLoop, &requestRestart);
                if (exitRenderLoop) {
                    break;
                }

                if (program->IsSessionRunning()) {
                    //program->PollActions();
                    program->RenderFrame();
                } else {
                    // Throttle loop since xrWaitFrame won't be called.
                    std::this_thread::sleep_for(std::chrono::milliseconds(250));
                }
            }

        } while (!quitKeyPressed && requestRestart);

        return 0;
    } catch (const std::exception& ex) {
        MonoPrint(ex.what());
        return 1;
    } catch (...) {
        MonoPrint("Unknown Error");
        return 1;
    }
}
