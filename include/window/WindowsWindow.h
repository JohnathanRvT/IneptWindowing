#pragma once

#ifdef INEPT_PLATFORM_WINDOWS
#include <window/WindowBase.h>

#include <Windows.h>
#include <memory>

namespace Inept::Windowing
{

    class WindowsWindow : public WindowBase
    {
    public:
        WindowsWindow(WindowBase* parent = nullptr, int width = 800, int height = 600, const std::string title = "Inept Window");

        WindowsWindow(const WindowsWindow&) = delete;
        WindowsWindow& operator=(const WindowsWindow&) = delete;
        WindowsWindow(WindowsWindow&&) = delete;
        WindowsWindow& operator=(WindowsWindow&&) = delete;

        virtual ~WindowsWindow();
        virtual void Update() override;
        virtual void Close() override;

        virtual void Show() override;
        virtual void Hide() override;
        virtual bool IsVisible() override;

        virtual void Move(int x, int y) override;
        virtual void Resize(int width, int height) override;

        virtual bool IsMaximized() override;
        virtual bool IsMinimized() override;
        virtual void Minimize() override;
        virtual void Maximize() override;
        virtual void Restore() override;

        virtual void ShowFullScreen() override;
        virtual void CloseFullScreen() override;
        virtual void SetFullscreen(bool fullscreen) override;
        virtual bool IsFocused() override;

        virtual void SetTitle(const std::string title)override;
        virtual const std::string GetTitle() override;

        virtual void SetPosition(int x, int y) override;
        virtual void SetSize(int width, int height) override;
        virtual int GetWidth() override;
        virtual int GetHeight() override;


        virtual void AddChild(WindowBase* child) override;
        virtual void RemoveChild(WindowBase* child) override;
        virtual void RemoveAllChildren() override;

        virtual WindowBase* GetParentWindow() override;
        virtual void SetParentWindow(WindowBase* parent) override;

        virtual HWND GetHandle() { return m_handle; }
    protected:
        HWND m_handle;
        virtual void Create(WindowBase* parent = nullptr, int width = 800, int height = 600, const std::string title = "Inept Window") override;
    };
}
#endif