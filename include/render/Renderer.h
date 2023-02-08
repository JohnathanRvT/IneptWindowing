#pragma once

#include <render/RendererBase.h>
using namespace Inept::Rendering;
#ifdef INEPT_PLATFORM_WINDOWS
#include <render/OpenGLRenderer.h>
#elif defined(INEPT_PLATFORM_MACOS)
#include <platform/MacOS/MacOSRendererBase.h>
#elif defined(INEPT_PLATFORM_ANDROID)
#include <platform/Android/AndroidRendererBase.h>
#elif defined(INEPT_PLATFORM_LINUX)
#include <platform/Linux/LinuxRendererBase.h>
#endif

namespace Inept::Rendering {
    // Static create function for cross platform support of WindowBase
    static RendererBase* Renderer(Inept::Windowing::WindowBase* window)
    {
#ifdef INEPT_PLATFORM_WINDOWS
        return new OpenGLRenderer();
#endif
        return nullptr;
    }
}