#pragma once

#ifdef INEPT_PLATFORM_WINDOWS
#include <platform/Windows/WindowsWindowBase.h>
#include <platform/Windows/WindowsInputManager.h>

#include <memory>

namespace Inept::Windowing
{
    WindowsWindowBase::WindowsWindowBase(WindowBase* parent, int width, int height, const wchar_t *title)
    {
        m_inputManager = new WindowsInputManager();
       // SetParent( parent ? parent : NULL);
        Create(parent, width, height, title);
    }

    WindowsWindowBase::~WindowsWindowBase()
    {
        Close();
    }

    void WindowsWindowBase::Create(WindowBase* parent, int width, int height, const wchar_t *title)
    {
        // Use the Windows API to create a window
        WNDCLASSW wc = {0};
        wc.lpfnWndProc = DefWindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszClassName = L"IneptWindow";
        RegisterClassW(&wc);

        m_handle = CreateWindowExW(
            0,
            L"IneptWindow",
           title,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            width,
            height,
            parent ? static_cast<WindowsWindowBase>(parent).GetHandle():NULL,
            NULL,
            GetModuleHandle(NULL),
            NULL);
    }

    void WindowsWindowBase::Close()
    {
        // Use the Windows API to close the window
        DestroyWindow(m_handle);
    }

    void WindowsWindowBase::Show()
    {
        // Use the Windows API to show the window
        ShowWindow(m_handle, SW_SHOW);
    }

    void WindowsWindowBase::Hide()
    {
        // Use the Windows API to hide the window
        ShowWindow(m_handle, SW_HIDE);
    }

    bool WindowsWindowBase::IsVisible()
    {
        // Use the Windows API to check if the window is visible
        return IsWindowVisible(m_handle) != 0;
    }
    void WindowsWindowBase::Move(int x, int y)
    {
        // Use the Windows API to move the window
        SetWindowPos(m_handle, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
    }
    void WindowsWindowBase::Resize(int width, int height)
    {
        // Use the Windows API to resize the window
        SetWindowPos(m_handle, 0, 0, 0, width, height, SWP_NOZORDER | SWP_NOMOVE);
    }
    bool WindowsWindowBase::IsMaximized()
    {
        // Use the Windows API to check if the window is maximized
        WINDOWPLACEMENT wp;
        wp.length = sizeof(wp);
        GetWindowPlacement(m_handle, &wp);
        return wp.showCmd == SW_MAXIMIZE;
    }
    bool WindowsWindowBase::IsMinimized()
    {
        // Use the Windows API to check if the window is minimized
        WINDOWPLACEMENT wp;
        wp.length = sizeof(wp);
        GetWindowPlacement(m_handle, &wp);
        return wp.showCmd == SW_MINIMIZE;
    }

    void WindowsWindowBase::Minimize()
    {
        // Use the Windows API to minimize the window
        ShowWindow(m_handle, SW_MINIMIZE);
    }

    void WindowsWindowBase::Maximize()
    {
        // Use the Windows API to maximize the window
        ShowWindow(m_handle, SW_MAXIMIZE);
    }

    void WindowsWindowBase::Restore()
    {
        // Use the Windows API to restore the window
        ShowWindow(m_handle, SW_RESTORE);
    }
    void WindowsWindowBase::ShowFullScreen()
    {
        // Use the Windows API to set the window to fullscreen
        SetWindowLongPtr(m_handle, GWL_STYLE, WS_POPUP | WS_VISIBLE);
        SetWindowPos(m_handle, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_SHOWWINDOW);
    }

    void WindowsWindowBase::CloseFullScreen()
    {
        // Use the Windows API to remove the window from fullscreen
        SetWindowLongPtr(m_handle, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
        SetWindowPos(m_handle, 0, 0, 0, 800, 600, SWP_SHOWWINDOW);
    }

    void WindowsWindowBase::SetFullscreen(bool fullscreen)
    {
        if (fullscreen)
            ShowFullScreen();
        else
            CloseFullScreen();
    }

    bool WindowsWindowBase::IsFocused()
    {
        // Use the Windows API to check if the window has focus
        return GetFocus() == m_handle;
    }

    void WindowsWindowBase::SetTitle(const wchar_t* title)
    {
        // Use the Windows API to set the window's title
        SetWindowTextW(m_handle, title);
    }

    const wchar_t* WindowsWindowBase::GetTitle()
    {
        // Use the Windows API to get the window's title
        int len = GetWindowTextLengthW(m_handle);
        wchar_t* title = new wchar_t[len + 1];
        GetWindowTextW(m_handle, title, len + 1);
        return title;
    }

    void WindowsWindowBase::SetPosition(int x, int y)
    {
        Move(x, y);
    }

    void WindowsWindowBase::SetSize(int width, int height)
    {
        Resize(width, height);
    }

    void WindowsWindowBase::AddChild(WindowBase* child)
    {
        // Use the Windows API to add a child window
        SetParent(static_cast<WindowsWindowBase*>(child)->m_handle, m_handle);
        child->SetParentWindow(this);
    }

    void WindowsWindowBase::RemoveChild(WindowBase* child)
    {
        // Use the Windows API to remove a child window
        SetParent(static_cast<WindowsWindowBase*>(child)->m_handle, NULL);
        child->SetParentWindow(nullptr);
    }

    void WindowsWindowBase::RemoveAllChildren()
    {
        // Use the Windows API to remove all child windows
        EnumChildWindows(
            m_handle, [](HWND hwnd, LPARAM lParam)
            {
        SetParent(hwnd, NULL);
        return TRUE; },
            0);
    }
    WindowBase* WindowsWindowBase::GetParentWindow()
    {
        return m_parent;
    }
    void WindowsWindowBase::SetParentWindow(WindowBase* parent)
    {
        m_parent = parent;
        SetParent(this->m_handle, static_cast<WindowsWindowBase>(parent).m_handle);
    }
} // namespace Inept::Windowing
#endif 