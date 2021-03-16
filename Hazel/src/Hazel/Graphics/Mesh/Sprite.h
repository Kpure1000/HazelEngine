#pragma once

#include "Mesh.h"

#include "Hazel/Utility/Math.h"

namespace hazel
{
	class Sprite : public Mesh
	{
	public:
		Sprite() :m_Size(0), m_UVOrg({ 0.0f,0.0f }), m_UV({ 1.0f,1.0f }) {}

		/// <summary>
		/// Sprite create by texCoord range
		/// </summary>
		/// <param name="size">Texture size</param>
		/// <param name="uv_origin">Origin coord</param>
		/// <param name="uv">UV coord</param>
		Sprite(glm::ivec2 size, glm::vec2 uv_origin = { 0.0f,0.0f }, glm::vec2 uv = { 1.0f,1.0f })
			:m_Size(size), m_UVOrg(uv_origin), m_UV(uv)
		{
			//auto left = -size.x * 0.5f;
			//auto buttom = -size.y * 0.5f;
			//auto right = size.x * 0.5f;
			//auto top = size.y * 0.5f;
			//std::vector<float> vert = {
			//left, buttom, 0.0f,
			//left, top, 0.0f,
			//right, top, 0.0f,
			//right, buttom, 0.0f,
			//};
			//std::vector<float> norm = {
			//	0,0,1,
			//	0,0,1,
			//	0,0,1
			//};
			//std::vector<float> texc = {
			//	uv_origin.x, uv_origin.y,
			//	uv_origin.x, uv.y,
			//	uv.x, uv.y,
			//	uv.x, uv_origin.y,
			//};
			//std::vector<unsigned int> indi = {
			//	0, 1, 3,  // first Triangle
			//	1, 2, 3   // second Triangle
			//};

			//BufferLayout layout_vert = {
			//	{ShaderDataType::Float3,"aPos"},
			//};
			//BufferLayout layout_norm = {
			//	{ShaderDataType::Float3,"aNormal"},
			//};
			//BufferLayout layout_texc = {
			//	{ShaderDataType::Float2,"aTexCoord"},
			//};

			//Ref<VertexBuffer> VBO_vert;
			//VBO_vert.reset(VertexBuffer::Create(sizeof(float) * vert.size()));
			//VBO_vert->SetLayout(layout_vert);
			//VBO_vert->SetData(vert.data(), sizeof(float) * vert.size());
			//m_VertexArray->AddVertexBuffer(VBO_vert);

			//Ref<VertexBuffer> VBO_norm;
			//VBO_norm.reset(VertexBuffer::Create(sizeof(float) * norm.size()));
			//VBO_norm->SetLayout(layout_norm);
			//VBO_norm->SetData(norm.data(), sizeof(float) * norm.size());
			//m_VertexArray->AddVertexBuffer(VBO_norm);

			//Ref<VertexBuffer> VBO_texc;
			//VBO_texc.reset(VertexBuffer::Create(sizeof(float) * texc.size()));
			//VBO_texc->SetLayout(layout_texc);
			//VBO_texc->SetData(texc.data(), sizeof(float) * texc.size());
			//m_VertexArray->AddVertexBuffer(VBO_texc);

			//Ref<IndexBuffer>EBO;
			//EBO.reset(IndexBuffer::Create(indi.data(),
			//	indi.size()));
			//m_VertexArray->SetIndexBuffer(EBO);
		}

		inline glm::ivec2 GetSize()const { return m_Size; }
		inline glm::vec4 GetUV()const { return { m_UVOrg ,m_UV }; }

	private:
		glm::ivec2 m_Size;
		glm::vec2 m_UVOrg;
		glm::vec2 m_UV;
	};
}