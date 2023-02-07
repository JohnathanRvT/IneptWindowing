#pragma once

#include <InputManagerBase.h>

namespace Inept::Windowing {

	class WindowsInputManager : public InputManagerBase
	{
	public:
		WindowsInputManager();
		virtual ~WindowsInputManager() = default;
		virtual bool IsKeyPressed(int key) override;
		virtual bool IsMouseButtonPressed(int button) override;
		virtual std::pair<int, int> GetMousePosition() override;
		virtual std::map<int, bool> GetKeyStates() override;
		virtual std::map<int, bool> GetMouseButtonStates() override;
		virtual void RegisterKeyCallback(int key, std::function<void(int)> callback) override;
		virtual void RegisterMouseButtonCallback(int button, std::function<void(int)> callback) override;
		virtual void RegisterMouseMoveCallback(std::function<void(int, int)> callback) override;
		virtual void PollEvents() override;
	private:
		std::map<int, bool> m_keyStates;
		std::map<int, bool> m_mouseButtonStates;
		std::map<int, std::function<void(int)>> m_keyCallbacks;
		std::map<int, std::function<void(int)>> m_mouseButtonCallbacks;
		void HandleWindowsMessage(UINT message, WPARAM wParam, LPARAM lParam);
	};
}