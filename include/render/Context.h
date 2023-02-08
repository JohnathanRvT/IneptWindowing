#pragma once

namespace Inept::Rendering
{
	class Context
	{
	public:
		Context() {}
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}
