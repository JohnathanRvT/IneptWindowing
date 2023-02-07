#ifdef INEPT_PLATFORM_WINDOWS
#include <Window.h>

#include <platform/Windows/WindowsInputManager.h>
#include <iostream>

namespace Inept::Windowing {

    WindowsInputManager::WindowsInputManager()
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

    bool WindowsInputManager::IsKeyPressed(int key)
    {
        // Use the Windows API to check if the key is pressed
        return (GetAsyncKeyState(key) & 0x8000) != 0;
    }

    bool WindowsInputManager::IsMouseButtonPressed(int button)
    {
        // Use the Windows API to check if the mouse button is pressed
        switch (button)
        {
        case 0:
            return (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
        case 1:
            return (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;
        case 2:
            return (GetAsyncKeyState(VK_MBUTTON) & 0x8000) != 0;
        default:
            return false;
        }
    }

    std::pair<int, int> WindowsInputManager::GetMousePosition()
    {
        POINT point;
        GetCursorPos(&point);
        return std::make_pair(point.x, point.y);
    }

    std::map<int, bool> WindowsInputManager::GetKeyStates()
    {
        return m_keyStates;
    }

    std::map<int, bool> WindowsInputManager::GetMouseButtonStates()
    {
        return m_mouseButtonStates;
    }

    void WindowsInputManager::RegisterKeyCallback(int key, std::function<void(int)> callback)
    {
        m_keyCallbacks[key] = callback;
    }

    void WindowsInputManager::RegisterMouseButtonCallback(int button, std::function<void(int)> callback)
    {
        m_mouseButtonCallbacks[button] = callback;
    }
    void WindowsInputManager::HandleWindowsMessage(UINT message, WPARAM wParam, LPARAM lParam)
    {
        std::cout << message << " " << wParam << "-" << lParam << std::endl;
        switch (message)
        {
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
            m_keyStates[wParam] = true;
            if (m_keyCallbacks.count(wParam) > 0)
            {
                m_keyCallbacks[wParam](wParam);
            }
            break;
        case WM_KEYUP:
        case WM_SYSKEYUP:
            m_keyStates[wParam] = false;
            break;
        case WM_LBUTTONDOWN:
            m_mouseButtonStates[0] = true;
            if (m_mouseButtonCallbacks.count(0) > 0)
            {
                m_mouseButtonCallbacks[0](0);
            }
            break;
        case WM_LBUTTONUP:
            m_mouseButtonStates[0] = false;
            break;
            // Repeat similar cases for other mouse buttons
        }
    }
    void WindowsInputManager::RegisterMouseMoveCallback(std::function<void(int, int)> callback)
    {
    }
    void WindowsInputManager::PollEvents()
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
        // Check for key press events
       // for (auto& [key, callback] : m_keyCallbacks)
       // {
       //     bool currentState = IsKeyPressed(key);
       //     if (currentState != m_keyStates[key])
       //     {
       //         m_keyStates[key] = currentState;
       //         if (currentState)
       //         {
       //             callback(key);
       //         }
       //     }
       // }
       //
       // Check for mouse button press events
       // for (auto& [button, callback] : m_mouseButtonCallbacks)
       // {
       //     bool currentState = IsMouseButtonPressed(button);
       //     if (currentState != m_mouseButtonStates[button])
       //     {
       //         m_mouseButtonStates[button] = currentState;
       //         if (currentState)
       //         {
       //             callback(button);
       //         }
       //     }
       // }
    }
}
#endif