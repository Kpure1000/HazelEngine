#pragma once

#include "Hazel/Core/Core.h"

namespace hazel
{
	class HAZEL_API RenderContext
	{
	public:

		virtual void Init() = 0;

		virtual void SwapBuffers() = 0;

	};
}