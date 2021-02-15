#pragma once

#include "Mesh.h"

#include <cmath>

#ifndef Pi
#define Pi 3.1415927f

#endif // !Pi


namespace hazel
{
	class CircleMesh : public Mesh
	{
	public:
		CircleMesh(int sizeCount = 100)
			:m_SideCount(sizeCount)
		{
			float R = 1.0f;

			std::vector<float> vert;
			auto vertexNum = (m_SideCount + 1) * 8;
			vert.resize(vertexNum);
			//  public original point
			//  position
			vert[0] = vert[1] = vert[2] = 0.0f;
			//  normal
			vert[3] = vert[4] = 0.0f;
			vert[5] = 1.0f;
			//  texCoords
			vert[6] = vert[7] = 0.5f;
			int sideCount = 0;
			for (size_t i = 8; i < vertexNum; i += 8)
			{
				//  position
				vert[i] = R * (float)cos(Pi * 2.0f / (float)m_SideCount * sideCount); //  x
				vert[i + 1] = R * (float)sin(Pi * 2.0f / (float)m_SideCount * sideCount); //  y
				vert[i + 2] = 0.0f; //  z
				//  normal
				vert[i + 3] = 0.0f; //  x
				vert[i + 4] = 0.0f; //  y
				vert[i + 5] = 1.0f; //  z
				//  texCoords
				vert[i + 6] = 0.5f + R * (float)cos(Pi * 2.0f / (float)m_SideCount * sideCount); //  u
				vert[i + 7] = 0.0f + R * (float)sin(Pi * 2.0f / (float)m_SideCount * sideCount); //  v
				sideCount++;
			}

			std::vector<unsigned int> indi;
			auto indiSize = 3 * m_SideCount;
			indi.resize(3 * m_SideCount);
			unsigned int indiCount = 1;
			for (int i = 0; i < indiSize - 3; i += 3)
			{
				indi[i] = 0;
				indi[i + 1] = indiCount;
				indi[i + 2] = indiCount + 1;
				indiCount++;
			}
			auto lastIndi = m_SideCount - 1;
			indi[lastIndi * 3] = 0;
			indi[lastIndi * 3 + 1] = m_SideCount;
			indi[lastIndi * 3 + 2] = 1;

			BufferLayout layout = {
				{ShaderDataType::Float3,"aPosition"},
				{ShaderDataType::Float3,"aNormal"},
				{ShaderDataType::Float2,"aTexCoord"},
			};

			Ref<VertexBuffer>VBO;
			VBO.reset(VertexBuffer::Create(vert.data(), sizeof(float) * vert.size()));
			VBO->SetLayout(layout);

			m_VertexArray->AddVertexBuffer(VBO);

			Ref<IndexBuffer>EBO;
			EBO.reset(IndexBuffer::Create(indi.data(),
				indi.size()));
			m_VertexArray->SetIndexBuffer(EBO);

		}

	private:

		int m_SideCount;
	};
}