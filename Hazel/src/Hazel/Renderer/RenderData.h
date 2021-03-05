#pragma once

#include "Hazel/Core/Core.h"
#include "Hazel/Utility/Math.h"

namespace hazel
{
	struct SceneData
	{
		glm::mat4 ViewProjectMat;
		glm::mat4 ProjectMat;
	};
}