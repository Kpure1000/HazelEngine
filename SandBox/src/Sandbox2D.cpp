#include "Sandbox2D.h"

using namespace hazel;

Sandbox2D::Sandbox2D()
	:m_CameraController((float)Application::GetInstance()->GetWindow().GetSize().x
		/ (float)Application::GetInstance()->GetWindow().GetSize().y, false, true)
{
	m_CameraController.EnableInput(false);
	m_CameraController.SetZoom(7.0f);

	m_ShaderManager = std::make_shared<ShaderManager>();
	auto tex_shader = m_ShaderManager->Load("../data/shader/Sandbox2D_tex.glsl");
	auto color_shader = m_ShaderManager->Load("../data/shader/Sandbox2D_color.glsl");
	auto blend_shader = m_ShaderManager->Load("../data/shader/Sandbox2D_blend.glsl");
	Ref<Texture2D> backTex;
	backTex.reset(Texture2D::Create());
	backTex->LoadFromFile("../data/texture/brickwall.jpg");

	player = std::make_shared<Player>();

	player->m_Shader = tex_shader;
	player->m_Mesh = std::make_shared<QuadMesh>();
	player->m_Trans->SetScale({ 2.0f,2.0f,1.0f });
	player->m_Trans->SetPosition({ 0.0f,-8.0f,1.0f });
	vy = jump_vy;
	player->m_Tex.reset(Texture2D::Create());
	player->m_Tex->LoadFromFile("../data/texture/sprite0.png");

	back[0] = std::make_shared<Player>();
	back[1] = std::make_shared<Player>();
	back[2] = std::make_shared<Player>();
	back[0]->m_Mesh = back[1]->m_Mesh = back[2]->m_Mesh
		= std::make_shared<QuadMesh>();
	int i = 0;
	for (auto it : back)
	{
		it->m_Trans->SetPosition({ 0.0f,-8.0f + 8.0f * i,-2.0f });
		it->m_Trans->SetScale({ 8.0f,8.0f,1.0f });
		it->m_Tex = backTex;
		it->m_Shader = blend_shader;
		i++;
	}

}

void Sandbox2D::OnAttach()
{
}

void Sandbox2D::OnDetch()
{
}

void Sandbox2D::OnUpdate()
{
	m_CameraController.OnUpdate();

	PlayerControl();
	BackgroundContorl();

	//  Draw
	RenderCommand::SetClearColor(glm::vec4(0.1f, 0.2f, 0.3f, 1.0f));
	RenderCommand::Clear();
	Renderer::BeginScene(m_CameraController.GetCamera());

	for (auto it : back)
	{
		it->m_Shader->Use();
		it->m_Tex->Bind(0);
		it->m_Shader->SetSampler2D("_tx", 0);
		it->m_Shader->SetVector4("_color", { m_QuadColor,1.0 });
		Renderer::Submit(it->m_Mesh, it->m_Trans, it->m_Shader);
	}

	player->m_Shader->Use();
	player->m_Tex->Bind(0);
	player->m_Shader->SetSampler2D("_tx", 0);
	Renderer::Submit(player->m_Mesh, player->m_Trans, player->m_Shader);

	Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Properties");
	ImGui::ColorEdit3("Quad Color", glm::value_ptr(m_QuadColor));
	ImGui::SliderFloat("Jump velocity", &jump_vy, 0.01f, 1.0f, "%.3f", 1.0f);
	ImGui::End();
}

void Sandbox2D::OnEvent(Event& ev)
{
	m_CameraController.OnEvent(ev);
	auto evd = EventDispatcher(ev);
	evd.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& ev)
		{
			if (ev.GetKeyCode() == Key::Escape)
			{
				Application::GetInstance()->Close();
				return true;
			}
			return false;
		});
}

void Sandbox2D::PlayerControl()
{
	p_pos = player->m_Trans->GetPosition();
	p_size = player->m_Trans->GetScale();

	if (Input::IsKeyPressed(Key::A)) {
		p_size.x = -std::abs(p_size.x);
		p_pos.x -= Time::deltaTime() * 10.0f;
	}
	if (Input::IsKeyPressed(Key::D)) {
		p_size.x = std::abs(p_size.x);
		p_pos.x += Time::deltaTime() * 10.0f;
	}

	if (p_pos.y < -8.0f)
	{
		vy = jump_vy;
	}
	else
	{
		vy -= gravity;
	}

	p_pos.y += vy;

	if (p_pos.y > maxHeight)
	{
		p_pos.y = maxHeight;
	}

	player->m_Trans->SetPosition(p_pos);
	player->m_Trans->SetScale(p_size);
}

void Sandbox2D::BackgroundContorl()
{
	if (player->m_Trans->GetPosition().y >= maxHeight)
	{
		for (size_t i = 0; i < back.size(); i++)
		{
			p_pos = back[i]->m_Trans->GetPosition();
			p_pos.y -= vy;
			if (p_pos.y < -12.0f)
				p_pos.y += 24.0f;
			back[i]->m_Trans->SetPosition(p_pos);
		}
	}
}
