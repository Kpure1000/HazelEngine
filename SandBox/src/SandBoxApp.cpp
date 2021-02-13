#include <Hazel.h>

#include <imgui.h>

class ExampleLayer : public hazel::Layer
{

public:
	ExampleLayer()
		: Layer("Eaxample"), m_CameraController(
			(float)hazel::Application::GetInstance()->GetWindow().GetSize().x
			/ (float)hazel::Application::GetInstance()->GetWindow().GetSize().y, false, true)
	{
		m_SMGR = std::make_shared<hazel::ShaderManager>();

		hazel::Ref<hazel::Shader> _shader = m_SMGR->Load("../data/shader/renderLayer.glsl");

		auto rd1 = std::make_shared<RenderData>();
		rd1->m_Mesh = std::make_shared<hazel::CubeMesh>();
		rd1->m_Mesh->GetTransform().SetScale(glm::vec3(1.5f));
		rd1->texture1.reset(hazel::Texture2D::Create());
		rd1->texture1->LoadFromFile("../data/texture/blending_transparent_window.png");
		rd1->texture2.reset(hazel::Texture2D::Create());
		rd1->texture2->LoadFromFile("../data/texture/checkborad.png");
		rd1->shader = _shader;
		rd1->shader->Use();
		rd1->texture1->Bind(0);
		rd1->shader->SetSampler2D("_diffuse", 0);
		rd1->texture2->Bind(1);
		rd1->shader->SetSampler2D("_diffuse", 1);
		rd1->drawCallFn = [rd1]() {
			rd1->shader->Use();

			rd1->texture2->Bind(1);
			rd1->shader->SetSampler2D("_diffuse", 1);
			rd1->m_Mesh->GetTransform().SetScale(glm::vec3(3.0f, 3.0f, 1.0f));

			rd1->m_Mesh->GetTransform().SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));
			hazel::Renderer::Submit(rd1->m_Mesh, rd1->shader);

			rd1->texture1->Bind(0);
			rd1->shader->SetSampler2D("_diffuse", 0);
			rd1->m_Mesh->GetTransform().SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

			rd1->m_Mesh->GetTransform().SetPosition(glm::vec3(-1.0f, -1.0f, -3.9999999f));
			hazel::Renderer::Submit(rd1->m_Mesh, rd1->shader);

			rd1->m_Mesh->GetTransform().SetPosition(glm::vec3(-0.5f, -0.5f, -0.3f));
			hazel::Renderer::Submit(rd1->m_Mesh, rd1->shader);

			rd1->m_Mesh->GetTransform().SetPosition(glm::vec3(0.0f, 0.0f, 0.5f));
			hazel::Renderer::Submit(rd1->m_Mesh, rd1->shader);

			rd1->m_Mesh->GetTransform().SetPosition(glm::vec3(0.5f, 0.5f, 0.7f));
			hazel::Renderer::Submit(rd1->m_Mesh, rd1->shader);

			rd1->m_Mesh->GetTransform().SetPosition(glm::vec3(1.0f, 1.0f, 0.9f));
			hazel::Renderer::Submit(rd1->m_Mesh, rd1->shader);

		};
		rd1->imGuiDrawCallFn = [this, rd1]() {
			auto pos = rd1->m_Mesh->GetTransform().GetPosition();
			ImGui::Begin("Properties 1");
			ImGui::SliderFloat3("Position", glm::value_ptr(pos), -3.0f, 3.0f, "%.3f", 1);
			ImGui::End();
			rd1->m_Mesh->GetTransform().SetPosition(pos);
		};

		m_RenderDatas.push_back(rd1);
	}

	void OnUpdate() override
	{
		m_CameraController.OnUpdate();
		//  Draw
		hazel::RenderCommand::SetClearColor(glm::vec4(0.5f, 0.6f, 0.5f, 1.0f));
		hazel::RenderCommand::Clear();
		hazel::Renderer::BeginScene(m_CameraController.GetCamera());
		for (auto& rd : m_RenderDatas) {
			rd->drawCallFn();
		}
		hazel::Renderer::EndScene();

	}

	void OnImGuiRender() override
	{
		//  Draw GUI
		for (auto& rd : m_RenderDatas) {
			rd->imGuiDrawCallFn();
		}
	}

	void OnEvent(hazel::Event& ev) override
	{
		m_CameraController.OnEvent(ev);
		auto evd = hazel::EventDispatcher(ev);
		evd.Dispatch<hazel::KeyPressedEvent>([](hazel::KeyPressedEvent& ev)
			{
				if (ev.GetKeyCode() == hazel::Key::Escape)
				{
					hazel::Application::GetInstance()->Close();
					return true;
				}
				return false;
			});
	}

private:

	hazel::OrthographicCameraController m_CameraController;

	struct RenderData
	{
		hazel::Ref<hazel::Mesh> m_Mesh;
		hazel::Ref<hazel::Shader> shader;
		hazel::Ref<hazel::Texture> texture1;
		hazel::Ref<hazel::Texture> texture2;
		hazel::Ref<hazel::Texture> texture3;

		std::function<void()> drawCallFn;
		std::function<void()> imGuiDrawCallFn;
	};

	std::vector<hazel::Ref<RenderData>> m_RenderDatas;

	hazel::Ref<hazel::ShaderManager> m_SMGR;

};

class SandBox : public hazel::Application
{
public:

	SandBox()
	{
		PushLayer(std::make_shared<ExampleLayer>());
	}

	~SandBox()
	{

	}

};

hazel::Ref<hazel::Application> hazel::CreateApplication()
{
	return std::make_shared<SandBox>();
}