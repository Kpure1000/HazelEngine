#include "Sandbox2D.h"

using namespace hazel;

Sandbox2D::Sandbox2D()
	:m_CameraController((float)Application::GetInstance()->GetWindow().GetSize().x
		/ (float)Application::GetInstance()->GetWindow().GetSize().y, false, true)
{
	srand((unsigned int)(time(NULL)));
	Application::GetInstance()->GetWindow().SetResizable(true);
	m_CameraController.EnableInput(false);
	m_ShaderManager = std::make_shared<ShaderManager>();

	//  load assets
	auto tex_shader = m_ShaderManager->Load("../data/shader/Sandbox2D_tex.glsl");
	auto color_shader = m_ShaderManager->Load("../data/shader/Sandbox2D_color.glsl");
	auto blend_shader = m_ShaderManager->Load("../data/shader/Sandbox2D_blend.glsl");
	auto freeTypeShader = m_ShaderManager->Load("../data/shader/freetype.glsl");
	Ref<Texture2D> backTex(Texture2D::Create());
	backTex->LoadFromFile("../data/texture/brickwall.jpg");
	Ref<Texture2D> playerTex(Texture2D::Create());
	playerTex->LoadFromFile("../data/texture/sprite0.png");
	Ref<Text> text = std::make_shared<Text>(Font("../data/font/3D Hand Drawns.ttf"), "Score: \n0000");
	
	//  init text
	m_TextShader = freeTypeShader;
	m_Text = text;
	m_Text->SetColor({ 0.9f,0.4f,0.8f,1.0f });
	m_TextTrans = std::make_shared<Transform>();
	m_TextTrans->SetPosition({ -240.0f,420.0f,2.0f });
	m_TextTrans->SetScale({ 0.4f,0.4f,1.0f });

	//  init player
	player = std::make_shared<Player>();
	player->m_Shader = tex_shader;
	player->m_Mesh = std::make_shared<QuadMesh>();
	player->m_Trans->SetScale({ 80.0f,80.0f,1.0f });
	player->m_Trans->SetPosition({ 0.0f,-300.0f,1.0f });
	vy = jump_vy;
	player->m_Tex = playerTex;

	//  init background
	auto backMesh = std::make_shared<QuadMesh>();
	int i = 0;
	for (auto& it : back)
	{
		it = std::make_shared<GameObject>();
		it->m_Mesh = backMesh;
		it->m_Trans->SetPosition({ 0.0f,-600.0f + 600.0f * i,-2.0f });
		it->m_Trans->SetScale({ 600.0f,600.0f,1.0f });
		it->m_Tex = backTex;
		it->m_Shader = blend_shader;
		i++;
	}

	//  init plats
	plats.resize(maxPlatNum);
	auto unitHiehgt = 1000.0f / (float)maxPlatNum;
	auto platMesh = std::make_shared<QuadMesh>();
	for (int i = 0; i < plats.size(); i++)
	{
		plats[i] = std::make_shared<Plat>();
		plats[i]->m_Mesh = platMesh;
		plats[i]->m_Trans->SetScale({ 65.0f,15.0f,1.0f });
		plats[i]->m_Trans->SetPosition({ -280.0f + (float)(rand() % 560),
			-512.0f + unitHiehgt * i,-1.0f });
		plats[i]->m_Shader = color_shader;
		plats[i]->_color = { 0.4f,0.7f,0.5f,1.0 };
	}
	plats[0]->m_Trans->SetPosition({ 0.0f,-515.0f,-1.0f });
}

void Sandbox2D::OnAttach()
{
}

void Sandbox2D::OnDetch()
{
}

void Sandbox2D::OnUpdate()
{
	//  TODO:
	//  1. SplitableTexture
	//  2. Sprite
	m_CameraController.OnUpdate();

	PlayerController();
	BackgroundContorller();
	PlatsController();

	//  Draw
	RenderCommand::SetClearColor(glm::vec4(0.1f, 0.2f, 0.3f, 1.0f));
	RenderCommand::Clear();
	Renderer::BeginScene(m_CameraController.GetCamera());

	//  render background
	for (auto it : back)
	{
		it->m_Shader->Use();
		it->m_Tex->Bind(0);
		it->m_Shader->SetSampler2D("_tx", 0);
		it->m_Shader->SetVector4("_color", { m_QuadColor,1.0 });
		Renderer::Submit(it->m_Mesh, it->m_Trans, it->m_Shader);
	}

	//  render plats
	for (auto plat : plats)
	{
		plat->m_Shader->Use();
		plat->m_Shader->SetVector4("_color", plat->_color);
		Renderer::Submit(plat->m_Mesh, plat->m_Trans, plat->m_Shader);
	}

	//  render player
	player->m_Shader->Use();
	player->m_Tex->Bind(0);
	player->m_Shader->SetSampler2D("_tx", 0);
	Renderer::Submit(player->m_Mesh, player->m_Trans, player->m_Shader);

	//  render text
	Renderer::Submit(m_Text, m_TextTrans, m_TextShader);

	Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
#ifdef HZ_DEBUG
	ImGui::Begin("Debugger");
	ImGui::ColorEdit3("Quad Color", glm::value_ptr(m_QuadColor));
	ImGui::Text("Current Plat Numbers: %d", curPlatNum);
	ImGui::DragFloat("Jump velocity", &jump_vy, 0.01f, 10.0f, 60.0f, "%.3f", 1.0f);
	ImGui::DragFloat("Move velocity", &moveSpeed, 0.01f, 30.0f, 50.0f, "%.3f", 1.0f);
	ImGui::End();
#endif // HZ_DEBUG
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
			if (ev.GetKeyCode() == Key::Minus)
			{
				curPlatNum = glm::clamp(curPlatNum - 1, 18, maxPlatNum);
			}
			if (ev.GetKeyCode() == Key::Equal)
			{
				curPlatNum = glm::clamp(curPlatNum + 1, 18, maxPlatNum);
			}
			return false;
		});
}

void Sandbox2D::PlayerController()
{
	p_pos = player->m_Trans->GetPosition();
	p_size = player->m_Trans->GetScale();

	// --input------
	bool left = Input::IsKeyPressed(Key::A), right = Input::IsKeyPressed(Key::D);

	// --vx---------
	vx += Time::deltaTime() * (-(int)left + (int)right) * moveSpeed;

	if (left == right)
		abs(vx) > 0.01f ? vx *= dragRatio : vx = 0.0f;

	vx = glm::clamp(vx, -maxVX, maxVX);

	// --vy---------

	vy = p_pos.y < deadLine || isJump ? jump_vy : vy - gravity;

	// --pos x------
	p_pos.x += vx;
	if (p_pos.x < -maxWidth)p_pos.x += 2.0f * maxWidth;
	else if (p_pos.x > maxWidth)p_pos.x -= 2.0f* maxWidth;

	// --pos y------
	if (vy < 0)
	{
		float minDis = FLT_MAX;
		int minIndex = -1;
		float platY, playerY = player->GetChecker().y;
		isJump = false;
		for (size_t i = 0; i < plats.size(); i++)
		{
#ifdef HZ_DEBUG
			plats[i]->_color = { 0.4f,0.7f,0.5f,1.0 };
#endif // HZ_DEBUG
			if (plats[i]->IsCollidedX(player->GetChecker().x))
			{
#ifdef HZ_DEBUG
				plats[i]->_color = { 0.2f,1.0f,0.1f,1.0 };
#endif // HZ_DEBUG
				platY = plats[i]->GetPlatHeight();
				if (0 < playerY - platY && playerY - platY < -vy)
				{
					isJump = true;
					if (playerY - platY < minDis)
					{
						minDis = playerY - platY;
						minIndex = i;
					}
				}
			}
		}

		if (vy < deadLine - playerY && deadLine - playerY < minDis)
		{
			//  game over
			isJump = true;
			Log::Info("---------GAME OVER---------");
			//  do something
			minDis = playerY - deadLine;
			p_pos.y -= minDis;
		}
		else if (isJump)
		{
			//  plat jump
			p_pos.y -= minDis;
#ifdef HZ_DEBUG
			plats[minIndex]->_color = { 0.9f,0.3f,0.6f,1.0 };
#endif // HZ_DEBUG
		}
		else
		{
			p_pos.y += vy;
		}
	}
	else
	{
		isJump = false;
		p_pos.y += vy;
		if (p_pos.y > maxHeight)
			p_pos.y = maxHeight;
	}


	// --size x (as simple animation)
	if (left != right)
		p_size.x = left ? -std::abs(p_size.x) : std::abs(p_size.x);

	// --apply------
	player->m_Trans->SetPosition(p_pos);
	player->m_Trans->SetScale(p_size);
}

void Sandbox2D::BackgroundContorller()
{
	if (player->m_Trans->GetPosition().y >= maxHeight)
	{
		for (size_t i = 0; i < back.size(); i++)
		{
			p_pos = back[i]->m_Trans->GetPosition();
			p_pos.y -= vy;
			if (p_pos.y < -900.0f)
				p_pos.y += 1800.0f;
			back[i]->m_Trans->SetPosition(p_pos);
		}
	}
}

void Sandbox2D::PlatsController()
{
	if (player->m_Trans->GetPosition().y >= maxHeight)
	{
		for (size_t i = 0; i < plats.size(); i++)
		{
			p_pos = plats[i]->m_Trans->GetPosition();
			p_pos.y -= vy;
			if (p_pos.y < -520.0f)
			{
				p_pos.x = -284.0f + (float)(rand() % 5680) / 10.0f;
				//  TODO 减少机制还有问题
				p_pos.y += 1040.0f + (maxPlatNum - curPlatNum) * 15.0f;
			}
			plats[i]->m_Trans->SetPosition(p_pos);
		}
	}
}
