#pragma once

#include <WindowBase.h>

#define INEPT_PLATFORM_WINDOWS

#ifdef INEPT_PLATFORM_WINDOWS
#include <platform/Windows/WindowsWindowBase.h>
#include <platform/Windows/WindowsInputManager.h>
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

namespace Inept::Windowing {
    // Static create function for cross platform support of WindowBase
    static WindowBase* Window(WindowBase* parent = nullptr, int width = 800, int height = 600, const wchar_t* title = L"Inept Window")
    {
#ifdef INEPT_PLATFORM_WINDOWS
        return new WindowsWindowBase(parent, width, height, title);
#endif
        return nullptr;
    }
}