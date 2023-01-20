#pragma once

#include <WindowBase.h>

namespace Inept::Windowing::Input {
  //  class InputManagerBase
  //  {
  //  public:
  //      InputManagerBase(std::shared_ptr<WindowBase> window){}
  //      ~InputManagerBase() {}
  //
  //      // Platform-agnostic functions for handling user input
  //      virtual void HandleKeyboardInput(int key, bool pressed) = 0;
  //      virtual void HandleMouseInput(int x, int y, int button, bool pressed) = 0;
  //      virtual void HandleTouchInput(int x, int y, int fingerId, bool pressed) = 0;
  //      virtual void HandleJoystickInput(int joystickId, int axis, float value) = 0;
  //
  //      // Platform-agnostic function for handling messages
  //      virtual void HandleMessage(int message, int wParam, int lParam) = 0;
  //  protected:
  //      std::shared_ptr<WindowBase> m_window;
  //  };
}