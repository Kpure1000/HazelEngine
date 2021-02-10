#include <Hazel.h>

#include <imgui.h>

class ExampleLayer : public hazel::Layer
{

public:
	ExampleLayer()
		: Layer("Eaxample"), m_Camera(glm::vec2(-1.0f, -2.0f), glm::vec2(2.0f, 3.0f))
	{
		auto rd1 = std::make_shared<RenderData>();
		rd1->m_Mesh = std::make_shared<hazel::CubeMesh>();
		rd1->m_Mesh->GetTransform().SetScale(glm::vec3(1.5f));
		rd1->shader.reset(hazel::Shader::Create("../data/shader/renderLayer.vert",
			"../data/shader/renderLayer.frag"));
		rd1->texture1.reset(hazel::Texture2D::Create());
		rd1->texture1->LoadFromFile("../data/texture/checkborad.png");
		rd1->texture1->Bind(0);
		rd1->shader->Use();
		rd1->shader->SetInt("_diffuse", 0);
		rd1->drawCallFn = [rd1]() {
			hazel::Renderer::Submit(rd1->m_Mesh, rd1->shader);
		};
		rd1->imGuiDrawCallFn = [this, rd1]() {
			auto pos = rd1->m_Mesh->GetTransform().GetPosition();
			auto caPos = m_Camera.GetPosition();
			ImGui::Begin("Properties");
			ImGui::SliderFloat3("Position", glm::value_ptr(pos), -3.0f, 3.0f, "%.3f", 1);
			ImGui::SliderFloat3("Camera Position", glm::value_ptr(caPos), -3.0f, 3.0f, "%.3f", 1);
			ImGui::End();
			rd1->m_Mesh->GetTransform().SetPosition(pos);
			m_Camera.SetPosition(caPos);
		};

		m_RenderDatas.push_back(rd1);
	}

	void OnUpdate() override
	{
		//  Logic update
		glm::vec3 mover(0);
		float rotate = 0.0f;
		float moveSpeed = 5.0f;
		float rotateSpeed = 20.0f;
		float ts = hazel::Time::deltaTime();
		if (hazel::Input::IsKeyPressed(hazel::Key::A))mover.x -= moveSpeed * ts;
		if (hazel::Input::IsKeyPressed(hazel::Key::D))mover.x += moveSpeed * ts;
		if (hazel::Input::IsKeyPressed(hazel::Key::W))mover.y += moveSpeed * ts;
		if (hazel::Input::IsKeyPressed(hazel::Key::S))mover.y -= moveSpeed * ts;
		if (hazel::Input::IsKeyPressed(hazel::Key::Q))rotate += rotateSpeed * ts;
		if (hazel::Input::IsKeyPressed(hazel::Key::E))rotate -= rotateSpeed * ts;

		m_Camera.SetPosition(m_Camera.GetPosition() + mover);
		m_Camera.SetRotation(m_Camera.GetRotation() + rotate);

		//  Draw
		hazel::RenderCommand::SetClearColor(glm::vec4(0.5f, 0.6f, 0.5f, 1.0f));
		hazel::RenderCommand::Clear();
		hazel::Renderer::BeginScene(m_Camera);
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

	hazel::OrthographicCamera m_Camera;

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