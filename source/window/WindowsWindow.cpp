#ifdef INEPT_PLATFORM_WINDOWS
#include <Window/WindowsWindow.h>

#include <Input/WindowsInput.h>
using namespace Inept::Input;

#include <render/OpenGL/OpenGLContext.h>
using namespace Inept::Rendering;

#include <Log.h>
using namespace Inept::Logging;

#include <memory>

namespace Inept::Windowing
{
    WindowsWindow::WindowsWindow(WindowBase* parent, int width, int height, const std::string title)
    {
        m_inputManager = new WindowsInput();
        Log::Init();

        Create(parent, width, height, title);

        m_context = new OpenGLContext(this);
        m_context->Init();
    }

    WindowsWindow::~WindowsWindow()
    {
        Close();
    }

    void WindowsWindow::Create(WindowBase* parent, int width, int height, const std::string title)
    {
        // Use the Windows API to create a window
        WNDCLASS wc = { 0 };
        wc.lpfnWndProc = DefWindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszClassName = L"IneptWindow";
        RegisterClass(&wc);
        std::wstring stemp = std::wstring(title.begin(), title.end());
        LPCWSTR sw = stemp.c_str();
        m_handle = CreateWindowEx(
            0,
            L"IneptWindow",
            sw,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            width,
            height,
            NULL,
            NULL,
            GetModuleHandle(NULL),
            NULL);

        if (m_handle == NULL)
            Log::logMessage(LOGERROR, "Window creation failed!");
        else {
            Log::logMessage(LOGINFO, std::format("New window {0} [width:{1},height:{2}] created", this->GetTitle(), width, height));
            if (parent != NULL)
                parent->AddChild(this);
            Log::logMessage(LOGINFO, std::format("Window {0} renderer inititialized", this->GetTitle()));
        }
    }
    
    void WindowsWindow::Update()
    {
        m_inputManager->PollEvents();
        m_context->SwapBuffers();
    }

    void WindowsWindow::Close()
    {
        //  // Use the Windows API to close the window
        if (DestroyWindow(m_handle))
            Log::logMessage(LOGINFO, std::format("Destroyed window {0}", this->GetTitle()));
        else
            Log::logMessage(LOGERROR, std::format("Destroying window {0} failed!", this->GetTitle()));
    }

    void WindowsWindow::Show()
    {
        // Use the Windows API to show the window
        ShowWindow(m_handle, SW_SHOW);
        Log::logMessage(LOGINFO, std::format("Showing window {0}", this->GetTitle()));
    }

    void WindowsWindow::Hide()
    {
        // Use the Windows API to hide the window
        ShowWindow(m_handle, SW_HIDE);
        Log::logMessage(LOGINFO, std::format("Hiding window {0}", this->GetTitle()));
    }

    bool WindowsWindow::IsVisible()
    {
        // Use the Windows API to check if the window is visible
        return IsWindowVisible(m_handle) != 0;
    }

    void WindowsWindow::Move(int x, int y)
    {
        // Use the Windows API to move the window
        if (SetWindowPos(m_handle, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE))
            Log::logMessage(LOGINFO, std::format("Moved window {0} to [{1},{2}]", this->GetTitle(), x, y));
        else
            Log::logMessage(LOGERROR, std::format("Moving window {0} failed!", this->GetTitle()));
    }

    void WindowsWindow::Resize(int width, int height)
    {
        // Use the Windows API to resize the window
        if (SetWindowPos(m_handle, 0, 0, 0, width, height, SWP_NOZORDER | SWP_NOMOVE))
            Log::logMessage(LOGINFO, std::format("Resizing window {0} to [{1},{2}]", this->GetTitle(), width, height));
        else
            Log::logMessage(LOGERROR, std::format("Resizing window {0} failed!", this->GetTitle()));
    }

    bool WindowsWindow::IsMaximized()
    {
        // Use the Windows API to check if the window is maximized
        WINDOWPLACEMENT wp;
        wp.length = sizeof(wp);
        GetWindowPlacement(m_handle, &wp);
        return wp.showCmd == SW_MAXIMIZE;
    }

    bool WindowsWindow::IsMinimized()
    {
        // Use the Windows API to check if the window is minimized
        WINDOWPLACEMENT wp;
        wp.length = sizeof(wp);
        GetWindowPlacement(m_handle, &wp);
        return wp.showCmd == SW_MINIMIZE;
    }

    void WindowsWindow::Minimize()
    {
        // Use the Windows API to minimize the window
        if (ShowWindow(m_handle, SW_MINIMIZE))
            Log::logMessage(LOGINFO, std::format("Minimizing window {0}", this->GetTitle()));
        else
            Log::logMessage(LOGERROR, std::format("Minimizing window {0} failed!", this->GetTitle()));
    }

    void WindowsWindow::Maximize()
    {
        // Use the Windows API to maximize the window
        if (ShowWindow(m_handle, SW_MAXIMIZE))
            Log::logMessage(LOGINFO, std::format("Maximizing window {0}", this->GetTitle()));
        else
            Log::logMessage(LOGERROR, std::format("Maximizing window {0} failed!", this->GetTitle()));
    }

    void WindowsWindow::Restore()
    {
        // Use the Windows API to restore the window
        if (ShowWindow(m_handle, SW_RESTORE))
            Log::logMessage(LOGINFO, std::format("Restoring window {0}", this->GetTitle()));
        else
            Log::logMessage(LOGERROR, std::format("Restoring window {0} failed!", this->GetTitle()));
    }

    void WindowsWindow::ShowFullScreen()
    {
        // Use the Windows API to set the window to fullscreen
        SetWindowLongPtr(m_handle, GWL_STYLE, WS_POPUP | WS_VISIBLE);
        if (SetWindowPos(m_handle, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_SHOWWINDOW))
            Log::logMessage(LOGINFO, std::format("Showing window {0} fullscreen", this->GetTitle()));
        else
            Log::logMessage(LOGERROR, std::format("Showing window {0} fullscreen failed!", this->GetTitle()));
    }

    void WindowsWindow::CloseFullScreen()
    {
        // Use the Windows API to remove the window from fullscreen
        SetWindowLongPtr(m_handle, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
        if (SetWindowPos(m_handle, 0, 0, 0, 800, 600, SWP_SHOWWINDOW))
            Log::logMessage(LOGINFO, std::format("Closing window {0} fullscreen", this->GetTitle()));
        else
            Log::logMessage(LOGERROR, std::format("Closing window {0} fullscreen failed!", this->GetTitle()));
    }

    void WindowsWindow::SetFullscreen(bool fullscreen)
    {
        if (fullscreen)
            ShowFullScreen();
        else
            CloseFullScreen();
    }

    bool WindowsWindow::IsFocused()
    {
        // Use the Windows API to check if the window has focus
        return GetFocus() == m_handle;
    }

    void WindowsWindow::SetTitle(const std::string title)
    {
        // Use the Windows API to set the window's title
        std::string oldtitle = this->GetTitle();
        std::wstring stemp = std::wstring(title.begin(), title.end());
        LPCWSTR sw = stemp.c_str();
        if (SetWindowText(m_handle, sw))
            Log::logMessage(LOGINFO, std::format("Setting window {0} title to {1}", oldtitle, title));
        else
            Log::logMessage(LOGERROR, std::format("Setting window {0} title to {1} failed", oldtitle, title));
    }


    const std::string WindowsWindow::GetTitle()
    {
        // Use the Windows API to get the window's title
        int len = GetWindowTextLength(m_handle);
        wchar_t* title = new wchar_t[len + 1];
        GetWindowText(m_handle, title, len + 1);
        std::wstring ws(title);
        std::string str(ws.begin(), ws.end());
        return str;
    }

    void WindowsWindow::SetPosition(int x, int y)
    {
        Move(x, y);
    }

    void WindowsWindow::SetSize(int width, int height)
    {
        Resize(width, height);
    }

    int WindowsWindow::GetWidth()
    {
        RECT rect;
        GetClientRect(m_handle, &rect);
        return rect.right - rect.left;
    }

    int WindowsWindow::GetHeight()
    {
        RECT rect;
        GetClientRect(m_handle, &rect);
        return rect.bottom - rect.top;
    }

    void WindowsWindow::AddChild(WindowBase* child)
    {
        // Use the Windows API to add a child window
        SetParent(static_cast<WindowsWindow*>(child)->m_handle, m_handle);
        child->SetParentWindow(this);
    }

    void WindowsWindow::RemoveChild(WindowBase* child)
    {
        // Use the Windows API to remove a child window
        SetParent(static_cast<WindowsWindow*>(child)->m_handle, NULL);
        SetParentWindow(NULL);
    }

    void WindowsWindow::RemoveAllChildren()
    {
        // Use the Windows API to remove all child windows
        EnumChildWindows(
            m_handle, [](HWND hwnd, LPARAM lParam)
            {
                SetParent(hwnd, NULL);
                return TRUE; },
            0);
    }
    WindowBase* WindowsWindow::GetParentWindow()
    {
        return m_parent;
    }

    void WindowsWindow::SetParentWindow(WindowBase* parent)
    {
        m_parent = parent;
    }
} // namespace Inept::Windowing
#endif 