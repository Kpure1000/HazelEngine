#include "hzpch.h"

#include <glad/glad.h>
#include <imgui.h>

#include "RenderLayer.h"

#include "Hazel/Log.h"
#include "Hazel/Time.h"
#include "Hazel/Application.h"
#include "Hazel/Graphics/Mesh/QuadMesh.h"

using std::shared_ptr;
using std::make_shared;

namespace hazel
{
	RenderLayer::RenderLayer()
		: Layer("RenderLayer")
	{
		auto rd1 = std::make_shared<RenderData>();
		m_RenderDatas.push_back(rd1);

		rd1->m_Mesh = std::make_shared<QuadMesh>();
		rd1->m_Mesh->GetTransform().SetScale(glm::vec3(1.5f));
		rd1->m_Mesh->GetTransform().SetOrigin(glm::vec3(0.5f));
		rd1->shader = std::make_shared<Shader>("../data/shader/example.vert",
			"../data/shader/example.frag");
		rd1->shader->Use();

		rd1->texture1= std::make_shared<Texture>();
		rd1->texture1->LoadFromFile("../data/texture/container.jpg");
		rd1->texture1->Bind(0);
		rd1->shader->SetInt("_diffuse", 0);

		rd1->shader->SetMatrix4("_model", rd1->m_Mesh->GetTransform().GetTransMat());

		rd1->drawCallFn = [rd1]() {
			rd1->shader->Use();
			rd1->shader->SetMatrix4("_model", rd1->m_Mesh->GetTransform().GetTransMat());
			Renderer::Submit(rd1->m_Mesh);
		};
		
		rd1->imGuiDrawCallFn = [rd1]() {
			auto pos = rd1->m_Mesh->GetTransform().GetPosition();
			float scale_val = 1.0f;
			ImGui::Begin("Oject Properties");
			ImGui::SliderFloat3("Position", glm::value_ptr(pos), -3.0f, 3.0f, "%.3f", 1);
			ImGui::SliderFloat("Scale", &scale_val, 0.1f, 3.0f, "%.3f", 1);
			ImGui::End();
			rd1->m_Mesh->GetTransform().SetPosition(pos);
			rd1->m_Mesh->GetTransform().SetScale(std::move(glm::vec3(scale_val)));
		};
	}
	
	void RenderLayer::OnAttach()
	{
	}
	
	void RenderLayer::OnDetch()
	{
	}
	
	void RenderLayer::OnUpdate()
	{
		for (auto& rd : m_RenderDatas) {
			rd->drawCallFn();
		}
	}
	
	void RenderLayer::OnImGuiRender()
	{
		for (auto& rd : m_RenderDatas) {
			rd->imGuiDrawCallFn();
		}
	}
	
	void RenderLayer::OnEvent(Event& ev)
	{
		EventDispatcher dispatcher(ev);
		dispatcher.Dispatch<WindowResizeEvent>([](WindowResizeEvent& ev)
			{
				auto app = Application::GetInstance();
				glViewport(0, 0, (unsigned int)app->GetWindow().GetSize().x,
					(unsigned int)app->GetWindow().GetSize().y);
				return false;
			});
	}
}