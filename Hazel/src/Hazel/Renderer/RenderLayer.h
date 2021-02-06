#pragma once

#include <vector>
#include <memory>

#include "Hazel/Layer.h"

#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/Texture.h"

#include "Hazel/Renderer/Renderer.h"

namespace hazel
{
	struct RenderData
	{
		//std::shared_ptr<VertexArray> m_VAO;
		std::shared_ptr<Mesh> m_Mesh;
		std::shared_ptr<Shader> shader;
		std::shared_ptr<Texture> texture1;
		std::shared_ptr<Texture> texture2;
		std::shared_ptr<Texture> texture3;

		std::function<void()> drawCallFn;
		std::function<void()> imGuiDrawCallFn;

	};

	/// <summary>
	/// Layer to render 
	/// </summary>
	class RenderLayer : public Layer
	{
	public:
		RenderLayer();

		virtual void OnAttach() override;
		virtual void OnDetch() override;
		virtual void OnUpdate() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;

	private:

		std::vector<std::shared_ptr<RenderData>> m_RenderDatas;

	};

}
