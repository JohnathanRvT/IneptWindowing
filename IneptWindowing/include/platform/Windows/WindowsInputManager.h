#pragma once

#include <InputManagerBase.h>

namespace Inept::Windowing::Input {

 //  class WindowsInputManager : public InputManagerBase
 //  {
 //  public:
 //      WindowsInputManager(std::shared_ptr<WindowsWindowBase> window) :InputManagerBase(window) {}
 //      ~WindowsInputManager() {}
 //
 //      // Platform-specific functions for handling user input
 //      virtual void HandleKeyboardInput(int key, bool pressed) override;
 //      virtual void HandleMouseInput(int x, int y, int button, bool pressed) override;
 //      virtual void HandleTouchInput(int x, int y, int fingerId, bool pressed) override;
 //      virtual void HandleJoystickInput(int joystickId, int axis, float value) override;
 //
 //      // Platform-specific function for handling messages
 //      virtual void HandleMessage(int message, int wParam, int lParam) override;
 //  protected:
 //      std::shared_ptr<WindowsWindowBase> m_window;
 //  };
}