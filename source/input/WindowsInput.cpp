#ifdef INEPT_PLATFORM_WINDOWS
#include <window/Window.h>

#include <Input/WindowsInput.h>

#include <Log.h>
using namespace Inept::Logging;

#include <iostream>

namespace Inept::Input {

    WindowsInput::WindowsInput()
    {
        // Initialize all key and mouse button states to false (not pressed)
        for (int i = 0; i < 256; i++)
        {
            m_keyStates[i] = false;
        }
        for (int i = 0; i < 3; i++)
        {
            m_mouseButtonStates[i] = false;
        }
    }

    bool WindowsInput::IsKeyPressed(int key)
    {
        // Use the Windows API to check if the key is pressed
        bool ret = (GetAsyncKeyState(key) & 0x8000) != 0;
        if (ret)
            Log::logMessage(LOGINFO, std::format("Key {} pressed", key));
        else
            Log::logMessage(LOGINFO, std::format("Key {} not pressed", key));
        return ret;
    }

    bool WindowsInput::IsMouseButtonPressed(int button)
    {
        // Use the Windows API to check if the mouse button is pressed
        bool ret = false;
        switch (button)
        {
        case 0:
            ret = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
            if (ret)
                Log::logMessage(LOGINFO, "Left Mouse Button pressed");
            else
                Log::logMessage(LOGINFO, "Left Mouse Button {} not pressed");
        case 1:
            ret = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;
            if (ret)
                Log::logMessage(LOGINFO, "Right Mouse Button {} pressed");
            else
                Log::logMessage(LOGINFO, "Right Mouse Button {} not pressed");
        case 2:
            ret = (GetAsyncKeyState(VK_MBUTTON) & 0x8000) != 0;
            if (ret)
                Log::logMessage(LOGINFO, "Middle Mouse Button {} pressed");
            else
                Log::logMessage(LOGINFO, "Middle Mouse Button {} not pressed");
        default:
            return false;
        }
        return ret;
    }

    std::pair<int, int> WindowsInput::GetMousePosition()
    {
        POINT point;
        GetCursorPos(&point);
        Log::logMessage(LOGINFO, std::format("Mouse position is [x:{0},y:{1}]", point.x, point.y));
        return std::make_pair(point.x, point.y);
    }

    std::map<int, bool> WindowsInput::GetKeyStates()
    {
        return m_keyStates;
    }

    std::map<int, bool> WindowsInput::GetMouseButtonStates()
    {
        return m_mouseButtonStates;
    }

    void WindowsInput::RegisterKeyCallback(int key, std::function<void(int)> callback)
    {
        m_keyCallbacks[key] = callback;
        Log::logMessage(LOGINFO, std::format("Key {0} callback set", key));
    }

    void WindowsInput::RegisterMouseButtonCallback(int button, std::function<void(int)> callback)
    {
        m_mouseButtonCallbacks[button] = callback;
        Log::logMessage(LOGINFO, std::format("Mouse button {0} callback set", button));
    }

    void WindowsInput::HandleWindowsMessage(UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_KEYDOWN:
        case WM_KEYUP:
        {
            int key = static_cast<int>(wParam);
            Log::logMessage(LOGINFO, std::format("Key event: {0} with keycode {1}", (message == WM_KEYDOWN ? "Key Down" : "Key Up"), key));
            break;
        }
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        {
            int button = 0;
            Log::logMessage(LOGINFO, std::format("Mouse button event: {0} with button code {1}", (message == WM_LBUTTONDOWN ? "Left Button Down" : "Left Button Up"), button));
            break;
        }
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        {
            int button = 1;
            Log::logMessage(LOGINFO, std::format("Mouse button event: {0} with button code {1}", (message == WM_RBUTTONDOWN ? "Right Button Down" : "Right Button Up"), button));
            break;
        }
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
        {
            int button = 2;
            Log::logMessage(LOGINFO, std::format("Mouse button event: {0} with button code {1}", (message == WM_MBUTTONDOWN ? "Middle Button Down" : "Middle Button Up"), button));
            break;
        }
        case WM_MOUSEMOVE:
        {
            int x = static_cast<int>(LOWORD(lParam));
            int y = static_cast<int>(HIWORD(lParam));

            Log::logMessage(LOGINFO, std::format("Mouse move event: X:{0} Y:{1}", x, y));
            break;
        }
        case WM_SIZE:
        {
            int width = static_cast<int>(LOWORD(lParam));
            int height = static_cast<int>(HIWORD(lParam));

            Log::logMessage(LOGINFO, std::format("Window resize event: Width:{0} Height:{1}", width, height));
            break;
        }
        case WM_CLOSE:
        {
            Log::logMessage(LOGINFO, "Window close event");
            break;
        }
        case WM_DESTROY:
        {
            Log::logMessage(LOGINFO, "Window destroy event");
            break;
        }
        default:
            break;
        }
    }

    void WindowsInput::RegisterMouseMoveCallback(std::function<void(int, int)> callback)
    {

    }

    void WindowsInput::PollEvents()
    {
        // Use the Windows API to check for any new input events

        // Get the next message from the queue
        MSG msg;
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // Handle the message
            HandleWindowsMessage(msg.message, msg.wParam, msg.lParam);
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}
#endif