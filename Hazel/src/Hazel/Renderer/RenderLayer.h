#pragma once

#include <vector>
#include <memory>

#include "Hazel/Layer.h"
#include "Hazel/Graphics/CubeMesh.h"
#include "Hazel/Graphics/SphereMesh.h"
#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/Texture.h"

namespace hazel
{
	struct RenderData
	{
		std::shared_ptr<Mesh> mesh;
		std::shared_ptr<Shader> shader;
		std::vector<std::shared_ptr<Texture>> textures;

		std::function<void()> drawCallFn;
		std::function<void()> imGuiDrawCallFn;

		RenderData(std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader)
			: mesh(mesh), shader(shader)
		{}

	};

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
		std::vector<std::shared_ptr<RenderData>> renderDataList;
	};

}
