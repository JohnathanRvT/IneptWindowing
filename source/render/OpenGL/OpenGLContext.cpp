#pragma once

#include "render/OpenGL/OpenGLContext.h"

#include <glad/glad.h>
#include <stdexcept>

namespace Inept::Rendering
{
	OpenGLContext::OpenGLContext(WindowBase* window):m_window(window) {
        
	}

	void OpenGLContext::Init() {
        // Create a device context.
        m_hDC = GetDC(static_cast<WindowsWindow*>(m_window)->GetHandle());

        // Set the pixel format.
        PIXELFORMATDESCRIPTOR pfd = { 0 };
        pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.nVersion = 1;
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 32;
        pfd.cDepthBits = 24;
        pfd.cStencilBits = 8;
        pfd.iLayerType = PFD_MAIN_PLANE;

        int pixelFormat = ChoosePixelFormat(m_hDC, &pfd);
        if (pixelFormat == 0)
        {
            throw std::runtime_error("Failed to choose a pixel format");
        }

        if (!SetPixelFormat(m_hDC, pixelFormat, &pfd))
        {
            throw std::runtime_error("Failed to set the pixel format");
        }

        // Create a rendering context.
        m_hRC = wglCreateContext(m_hDC);
        if (m_hRC == nullptr)
        {
            throw std::runtime_error("Failed to create a rendering context");
        }

        // Choose context currently used
        if (!wglMakeCurrent(m_hDC, m_hRC))
        {
            throw std::runtime_error("Failed to make the rendering context current");
        }

        // Initialize GLAD
        if (!gladLoadGL())
        {
            throw std::runtime_error("Failed to initialize Glad");
        }
	}
	void OpenGLContext::SwapBuffers() {
        glClearColor(0.2f,1,0.2f,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        ::SwapBuffers(m_hDC);
	}
}
