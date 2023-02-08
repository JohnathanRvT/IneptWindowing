#pragma once
#include "render/Context.h"

#include <window/WindowsWindow.h>
using namespace Inept::Windowing;

namespace Inept::Rendering
{
	class OpenGLContext : public Context
	{
	public:
		OpenGLContext(WindowBase* window);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		WindowBase* m_window;

		HDC m_hDC;
		HGLRC m_hRC;
	};
}
