#include "hzpch.h"

#include <glad/glad.h>

#include "RenderLayer.h"
#include "Hazel/Log.h"

#include "Hazel/Time.h"

#include <imgui.h>

using std::shared_ptr;
using std::make_shared;

namespace hazel
{
	RenderLayer::RenderLayer()
		: Layer("RenderLayer")
	{
		
	}
	void RenderLayer::OnAttach()
	{
		auto cube = make_shared<SphereMesh>();

		auto shader = make_shared<Shader>("../data/shader/example.vert", "../data/shader/example.frag");
		shader->Use();
		shader->SetMatrix4("_model", cube->GetTransform().GetTransMat());
		auto rd1 = make_shared<RenderData>(cube, shader);
		rd1->drawCallFn = [rd1]()
		{
			rd1->shader->Use();
			rd1->shader->SetMatrix4("_model", rd1->mesh->GetTransform().GetTransMat());

			glBindVertexArray(rd1->mesh->GetVAO());
			glDrawArrays(GL_TRIANGLES, 0, (GLsizei)(rd1->mesh->GetVertices().size()));
		};
		rd1->imGuiDrawCallFn = [rd1]()
		{
			static auto rtAxis = glm::vec3(0.2f, 0.3f, 0.6f);
			static float rt_speed = 0.0f;
			static float rt_val = 0.0f;
			//static bool show = true;
			ImGui::Begin("Properties");
			ImGui::SliderFloat3("Cube pos:", glm::value_ptr(rtAxis), -2.0f, 2.0f, "%.3f", 1);
			ImGui::SliderFloat("Rotate speed", &rt_speed, -40.0f, 40.f, "%.3f", 1);
			ImGui::Text("Rotate value: %.3f", rt_val);
			ImGui::End();
			rd1->mesh->GetTransform().SetRotation(rtAxis, rt_val += rt_speed * Time::deltaTime());
		};
		renderDataList.push_back(rd1);

	}
	void RenderLayer::OnDetch()
	{
	}
	void RenderLayer::OnUpdate()
	{
		for (auto rd : renderDataList)
		{
			rd->drawCallFn();
		}
	}
	void RenderLayer::OnImGuiRender()
	{
		for (auto rd : renderDataList)
		{
			rd->imGuiDrawCallFn();
		}
	}
	void RenderLayer::OnEvent(Event& e)
	{
	}
}