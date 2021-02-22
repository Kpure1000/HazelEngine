#pragma once

#include "Mesh.h"

#include "Hazel/Utility/Math.h"

namespace hazel
{
	class Sprite : public Mesh
	{
	public:
		/// <summary>
		/// Sprite create by texture size
		/// </summary>
		/// <param name="size">Texture size</param>
		Sprite(glm::ivec2 size)
			:m_Size(size)
		{
			auto left = (float)-size.x * 0.5f;
			auto buttom = (float)-size.y * 0.5f;
			auto right = (float)size.x * 0.5f;
			auto top = (float)size.y * 0.5f;
			std::vector<float> vert = {
			left, buttom, 0.0f,		0, 0, 1,  0, 0,
			left, top, 0.0f,		0, 0, 1,  0, 1,
			right, top, 0.0f,		0, 0, 1,  1, 1,
			right, buttom, 0.0f,	0, 0, 1,  1, 0,
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

		/// <summary>
		/// Sprite create by texCoord range
		/// </summary>
		/// <param name="size">Texture size</param>
		/// <param name="uv_origin">Origin coord</param>
		/// <param name="uv">UV coord</param>
		Sprite(glm::ivec2 size, glm::vec2 uv_origin, glm::vec2 uv)
			:m_Size(size)
		{
			auto left = -size.x * 0.5f;
			auto buttom = -size.y * 0.5f;
			auto right = size.x * 0.5f;
			auto top = size.y * 0.5f;
			std::vector<float> vert = {
			left, buttom, 0.0f,		0, 0, 1,  uv_origin.x, uv_origin.y,
			left, top, 0.0f,		0, 0, 1,  uv_origin.x, uv.y,
			right, top, 0.0f,		0, 0, 1,  uv.x, uv.y,
			right, buttom, 0.0f,	0, 0, 1,  uv.x, uv_origin.y,
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

		inline glm::ivec2 GetSize() { return m_Size; }

	private:
		glm::ivec2 m_Size;
	};
}