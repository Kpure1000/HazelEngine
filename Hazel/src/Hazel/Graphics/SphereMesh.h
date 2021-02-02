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
			Init();
		}

	private:

		virtual void Init() override;

		int m_lerpNum;
	};
}