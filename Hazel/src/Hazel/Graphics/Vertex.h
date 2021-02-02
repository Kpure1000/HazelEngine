#pragma once

#include "Hazel/Core/Core.h"

#include <glm/glm.hpp>

namespace hazel
{
	struct HAZEL_API Vertex
	{
		/// <summary>
		/// Position
		/// </summary>
		glm::vec3 position;

		/// <summary>
		/// Normal
		/// </summary>
		glm::vec3 normal;

		/// <summary>
		/// Texture Coords
		/// </summary>
		glm::vec2 texCoords;

		//  attatch:

		/// <summary>
		/// Tangent
		/// </summary>
		glm::vec3 tangent;

		/// <summary>
		/// Bitangent
		/// </summary>
		glm::vec3 bitangent;


		[[maybe_unused]]
		/// <summary>
		/// May used for Sprite
		/// </summary>
		glm::vec3 color;
	};
}