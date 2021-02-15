#pragma once

#include "Mesh.h"

namespace hazel
{
	class QuadMesh : public Mesh
	{
	public:
		QuadMesh()
		{
			std::vector<float> vert = {
			-0.5f, -0.5f, 0.0f,  0, 0, 1,  0, 0,
			-0.5f, 0.5f, 0.0f,  0, 0, 1,  0, 1,
		    0.5f, 0.5f, 0.0f,  0, 0, 1,  1, 1,
		    0.5f, -0.5f, 0.0f,  0, 0, 1,  1, 0,
			};
			std::vector<unsigned int> indi = {
				0, 1, 3,  // first Triangle
				1, 2, 3   // second Triangle
			};

			BufferLayout layout = {
				{ShaderDataType::Float3,"aPos"},
				{ShaderDataType::Float3,"aNormal"},
				{ShaderDataType::Float2,"aTexCoord"},
			};

			Ref<VertexBuffer> VBO;
			VBO.reset(VertexBuffer::Create(vert.data(), sizeof(float) * vert.size()));
			VBO->SetLayout(layout);
			m_VertexArray->AddVertexBuffer(VBO);

			Ref<IndexBuffer>EBO;
			EBO.reset(IndexBuffer::Create(indi.data(),
				indi.size()));
			m_VertexArray->SetIndexBuffer(EBO);

		}
	};
}