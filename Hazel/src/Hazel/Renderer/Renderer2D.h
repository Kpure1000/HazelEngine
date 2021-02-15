#pragma once

#include "Camera/OrthographicCamera.h"

namespace hazel
{
	class HAZEL_API Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
	};
}