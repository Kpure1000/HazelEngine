#pragma once

#include "Mesh.h"

namespace hazel
{
	class SphereMesh : public Mesh
	{
	public:
		SphereMesh() 
			:m_lerpNum(100)
		{
			std::vector<float> vert;
			std::vector<unsigned int> indi;

			
		}

	private:

		int m_lerpNum;
	};
}