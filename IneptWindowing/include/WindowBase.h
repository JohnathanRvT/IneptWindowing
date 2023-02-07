#pragma once

#include <InputManagerBase.h>

namespace Inept::Windowing
{
    /*
    The WindowBase class is a cross-platform implementation for creating a window in C++.
    It abstracts away platform-specific code,
    allowing for the creation of a window that can be used on multiple operating systems,
    such as Windows, MacOS, Android and Linux.
    This allows for a consistent and streamlined development experience when
    creating graphical applications in C++.
    */
    class WindowBase
    {
    public:
        /*
         * @brief Constructor for the WindowBase class.
         * @param parent A pointer to the parent window.
         * @param width The width of the window.
         * @param height The height of the window.
         * @param title The title of the window.
         */
        WindowBase(WindowBase* parent = nullptr, int width = 800, int height = 600, const wchar_t* title = L"Inept Window") {}

        /*
         * @brief Virtual destructor for the WindowBase class.
         */
        virtual ~WindowBase() = default;

        /*The default constructor, copy constructor,
        copy assignment operator, move constructor,
        and move assignment operator of WindowBase have been deleted.
        This is done to prevent unwanted copying or moving of WindowBase objects
        as it may not make sense or have unexpected behavior in certain cases.
        */
        WindowBase(const WindowBase&) = delete;
        WindowBase& operator=(const WindowBase&) = delete;
        WindowBase(WindowBase&&) = delete;
        WindowBase& operator=(WindowBase&&) = delete;

        /*
         * @brief Close the window.
         */
        virtual void Close() = 0;

        /*
         * @brief Show the window.
         */
        virtual void Show() = 0;

        /*
         * @brief Hide the window.
         */
        virtual void Hide() = 0;

        /*
         * @brief Check if the window is currently visible.
         * @return true if the window is visible, false otherwise.
         */
        virtual bool IsVisible() = 0;

        /*
         * @brief Move the window to a specific position.
         * @param x The x-coordinate of the new position.
         * @param y The y-coordinate of the new position.
         */
        virtual void Move(int x, int y) = 0;

        /*
         * @brief Resize the window to a specific size.
         * @param width The new width of the window.
         * @param height The new height of the window.
         */
        virtual void Resize(int width, int height) = 0;

        /*
         * @brief Check if the window is currently maximized.
         * @return true if the window is maximized, false otherwise.
         */
        virtual bool IsMaximized() = 0;

        /*
         * @brief Check if the window is currently minimized.
         * @return true if the window is minimized, false otherwise.
         */
        virtual bool IsMinimized() = 0;

        /*
         * @brief Minimize the window.
         */
        virtual void Minimize() = 0;

        /*
         *  @brief Maximize the window.
         */
        virtual void Maximize() = 0;

        /*
         * @brief Restore the window to its previous state (before it was minimized or maximized).
         */
        virtual void Restore() = 0;

        /*
         * @brief Show the window in full-screen mode.
         */
        virtual void ShowFullScreen() = 0;

        /*
         * @brief Exit full-screen mode and restore the window to its previous size and position.
         */
        virtual void CloseFullScreen() = 0;

        /*
         * @brief Set the full-screen state of the window.
         * @param fullscreen true to show the window in full-screen mode, false to exit full-screen mode.
         */
        virtual void SetFullscreen(bool fullscreen) = 0;

        /*
         * @brief Check if the window currently has focus.
         * @return true if the window has focus, false otherwise.
         */
        virtual bool IsFocused() = 0;

        /*
         * @brief Set the title of the window.
         * @param title The new title of the window.
         */
        virtual void SetTitle(const wchar_t* title) = 0;

        /*
         * @brief Get the title of the window.
         * @return The title of the window.
         */
        virtual const wchar_t* GetTitle() = 0;

        /*
         * @brief Set the position of the window.
         * @param x The x-coordinate of the new position.
         * @param y The y-coordinate of the new position.
         */
        virtual void SetPosition(int x, int y) = 0;

        /*
         * @brief Set the size of the window.
         * @param width The new width of the window.
         * @param height The new height of the window.
         */
        virtual void SetSize(int width, int height) = 0;

        /*
         * @brief Add a child window to the current window.
         * @param child A pointer to the child window.
         */
        virtual void AddChild(WindowBase* child) = 0;

        /*
         * @brief Remove a child window from the current window.
         * @param child A pointer to the child window.
         */
        virtual void RemoveChild(WindowBase* child) = 0;

        /*
         * @brief Remove all child windows from the current window.
         */
        virtual void RemoveAllChildren() = 0;

        /*
         * @brief Return the parent of the window if any
         */
        virtual WindowBase* GetParentWindow() = 0;

        /*
       * @brief Sets the parent of the window
       */
        virtual void SetParentWindow(WindowBase* parent) = 0;

        /*
         * @brief Get the input manager for the window.
         * @return A pointer to the input manager for the window.
         */
       InputManagerBase* GetInputManager() { return m_inputManager; }

    protected:
        InputManagerBase* m_inputManager;
        WindowBase* m_parent;

        virtual void Create(WindowBase* parent = nullptr, int width = 800, int height = 600, const wchar_t* title = L"Inept Window") = 0;
    };
} // namespace Inept::Windowing