#pragma once

#include <window/WindowBase.h>

#ifdef INEPT_PLATFORM_WINDOWS
#include <window/WindowsWindow.h>
//#include <input/WindowsInputManager.h>
#elif defined(INEPT_PLATFORM_MACOS)
#include <platform/MacOS/MacOSWindowBase.h>
#include <platform/MacOS/MacOSInputManager.h>
#elif defined(INEPT_PLATFORM_ANDROID)
#include <platform/Android/AndroidWindowBase.h>
#include <platform/Android/AndroidInputManager.h>
#elif defined(INEPT_PLATFORM_LINUX)
#include <platform/Linux/LinuxWindowBase.h>
#include <platform/Linux/LinuxInputManager.h>
#endif

namespace Inept::Windowing
{
    // Static create function for cross platform support of WindowBase
    static WindowBase* CreateIneptWindow(WindowBase* parent = nullptr, int width = 800, int height = 600, const std::string title = "Inept Window")
    {
#ifdef INEPT_PLATFORM_WINDOWS
        return new WindowsWindow(parent, width, height, title);
#else
        return nullptr;
#endif
    }
}