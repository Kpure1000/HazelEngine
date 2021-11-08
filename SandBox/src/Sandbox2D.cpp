#include "Sandbox2D.h"

using namespace hazel;

Sandbox2D::Sandbox2D()
	:m_CameraController((float)Application::GetInstance()->GetWindow().GetSize().x
		/ (float)Application::GetInstance()->GetWindow().GetSize().y, false, true)
{
	HZ_PROFILE_FUNCTION();

	srand((unsigned int)(time(NULL)));
	Application::GetInstance()->GetWindow().SetResizable(true);
	m_CameraController.EnableInput(false);
	
	//  load assets
	m_ShaderManager = std::make_shared<ShaderManager>();
	m_ShaderManager->Load("../data/shader/Sandbox2D_tex.glsl");
	m_ShaderManager->Load("../data/shader/Sandbox2D_color.glsl");
	m_ShaderManager->Load("../data/shader/Sandbox2D_blend.glsl");
	m_ShaderManager->Load("../data/shader/freetype.glsl");

	Ref<Texture2D> backTex(Texture2D::Create());
	backTex->LoadFromFile("../data/texture/back0.psd");
	Ref<Texture2D> playerTex(Texture2D::Create());
	playerTex->LoadFromFile("../data/texture/sprite0.png");
	Ref<Texture2D> platTex(Texture2D::Create());
	platTex->LoadFromFile("../data/texture/plats.psd");

	auto socreFont = Font("../data/font/3D Hand Drawns.ttf");

	//  init particle
	particle = std::make_shared<ParticleSystem<Sprite, 128>>(0.8f);
	particle->m_Shader = m_ShaderManager->Get("Sandbox2D_color");
	for (auto& it : particle->ptc())
	{
		it.m_Mesh = Sprite({ 1.0f,1.0f });
		it.m_Trans.SetScale({ 10.0f,10.0f,1.0f });
	}

	//  init text
	Ref<Text> text = std::make_shared<Text>(socreFont);
	m_TextShader = m_ShaderManager->Get("freetype");
	m_Text = text;
	m_Text->SetColor({ 1.0f,0.3f,0.3f,1.0f });
	m_TextTrans = std::make_shared<Transform>();
	m_TextTrans->SetPosition({ -263.0f,393.0f,2.0f });
	m_TextTrans->SetScale({ 0.4f,0.4f,1.0f });

	//  init player
	player = std::make_shared<Player>();
	player->m_Shader = m_ShaderManager->Get("Sandbox2D_tex");
	player->m_Sprite = Sprite(playerTex->GetSize());
	player->m_Trans.SetScale({ 0.1f,0.1f,1.0f });
	player->m_Trans.SetPosition({ 0.0f,-300.0f,1.0f });
	vy = jump_vy;
	player->m_Tex = playerTex;

	//  init background
	sp_back.push_back(Sprite(
		{ backTex->GetSize().x,backTex->GetSize().y / 5 },
		{ 0.0f,0.8f }, { 1.0f,1.0f }));
	sp_back.push_back(Sprite(
		{ backTex->GetSize().x,backTex->GetSize().y / 5 },
		{ 0.0f,0.6f }, { 1.0f,0.8f }));
	sp_back.push_back(Sprite(
		{ backTex->GetSize().x,backTex->GetSize().y / 5 },
		{ 0.0f,0.4f }, { 1.0f,0.6f }));
	sp_back.push_back(Sprite(
		{ backTex->GetSize().x,backTex->GetSize().y / 5 },
		{ 0.0f,0.2f }, { 1.0f,0.4f }));
	sp_back.push_back(Sprite(
		{ backTex->GetSize().x,backTex->GetSize().y / 5 },
		{ 0.0f,0.0f }, { 1.0f,0.2f }));
	int i = 0;
	for (auto& it : back)
	{
		it = std::make_shared<GameObject>();
		it->m_Sprite = sp_back[rand() % sp_back.size()];
		it->m_Trans.SetPosition({ 0.0f,-600.0f + 1200.0f / back.size() * i,-2.0f });
		it->m_Trans.SetScale({ 0.5859f,0.5859f,1.0f });
		it->m_Tex = backTex;
		it->m_Shader = m_ShaderManager->Get("Sandbox2D_blend");
		i++;
	}

	//  init plats
	sp_normalPlats.push_back(Sprite(
		{ platTex->GetSize().x / 2,platTex->GetSize().y / 4 },
		{ 0.0f,0.75f }, { 0.5f,1.0f }
	));
	sp_normalPlats.push_back(Sprite(
		{ platTex->GetSize().x / 2,platTex->GetSize().y / 4 },
		{ 0.0f,0.5f }, { 0.5f,0.75f }
	));
	sp_normalPlats.push_back(Sprite(
		{ platTex->GetSize().x / 2,platTex->GetSize().y / 4 },
		{ 0.0f,0.25f }, { 0.5f,0.5f }
	));
	sp_normalPlats.push_back(Sprite(
		{ platTex->GetSize().x / 2,platTex->GetSize().y / 4 },
		{ 0.0f,0.0f }, { 0.5f,0.25f }
	));
	sp_weakPlats.push_back(Sprite(
		{ platTex->GetSize().x / 2,platTex->GetSize().y / 4 },
		{ 0.5f,0.75f }, { 1.0f,1.0f }
	));

	plats.resize(maxPlatNum);
	auto curMaxHeight = -512.0f;
	curPlatNum = maxPlatNum;
	auto bldShader = m_ShaderManager->Get("Sandbox2D_blend");
	for (int i = 0; i < plats.size(); i++)
	{
		plats[i].m_Shader = bldShader;
		plats[i].m_Tex = platTex;

		plats[i].m_Trans.SetScale({ 0.06f,0.06f,1.0f });
		plats[i].m_Trans.SetPosition({
			-270.0f + (float)(rand() % 540),
			curMaxHeight + 1024.0f / curPlatNum,
			-1.0f
			});
		curMaxHeight += 1024.0f / curPlatNum;

		CreatePlat(plats[i]);
	}
	plats[0].m_Trans.SetPosition({ 0.0f,-500.0f,-1.0f });
	plats[0].m_Type = Plat::Type::NORMAL;
	plats[0].m_Sprite = sp_normalPlats[rand() % sp_normalPlats.size()];
}

void Sandbox2D::OnAttach()
{
}

void Sandbox2D::OnDetch()
{
}

void Sandbox2D::OnUpdate()
{
	HZ_PROFILE_FUNCTION();

	{
		HZ_PROFILE_SCOPE("Update CameraController");
		m_CameraController.OnUpdate();
	}

	{
		HZ_PROFILE_SCOPE("Update GamePlay Controller");
		BackgroundContorller();
		if (!isQuit) {
			DifficultyController();
			PlayerController();
			PlatsController();
		}
		TextController();
	}

	{
		HZ_PROFILE_SCOPE("Particle update");
		particle->Update(gravity * Time::deltaTime() * 70.0f,
			player->m_Trans.GetPosition().y >= maxHeight || isGameOver ? -vy : 0.0f);
	}

	{
		HZ_PROFILE_SCOPE("SetClear");
		RenderCommand::SetClearColor({ m_BackColor, 1.0f });
		RenderCommand::Clear();
	}

	SpriteRenderer::ResetState();
	{
		HZ_PROFILE_FUNCTION();
		SpriteRenderer::BeginScene(m_CameraController.GetCamera());
	}

	{
		HZ_PROFILE_SCOPE("Rendering");

		{
			HZ_PROFILE_SCOPE("Rendering Background");
			if (isRenderBackground) {
				for (auto& it : back)
				{
					SpriteRenderer::Submit(it->m_Sprite, it->m_Trans, it->m_Tex);
				}
			}
		}

		{
			HZ_PROFILE_SCOPE("Rendering Plats");
			for (auto& plat : plats)
			{
				if (plat.m_Color.a > 0.1f && plat.m_Trans.GetPosition().y < 520.0f) {
					SpriteRenderer::Submit(plat.m_Sprite, plat.m_Trans, plat.m_Tex, plat.m_Color);
				}
			}
		}

		{
			HZ_PROFILE_SCOPE("Rendering Praticles");
			for (auto& ptc : particle->ptc())
			{
				if (ptc.lifeTime > 0.0f) {
					SpriteRenderer::Submit(ptc.m_Mesh, ptc.m_Trans, particle->m_Tex, ptc.m_Color);
				}
			}
		}

		{
			HZ_PROFILE_SCOPE("Rendering Player");
			p_pos = player->m_Trans.GetPosition();
			if (!isGameOver && p_pos.y < 5 * maxHeight)
				SpriteRenderer::Submit(player->m_Sprite, player->m_Trans, player->m_Tex);
		}

		SpriteRenderer::NewBatch();

		{
			HZ_PROFILE_SCOPE("Rendering Text");
			SpriteRenderer::Submit(*m_Text, *m_TextTrans);
		}
	}

	{
		HZ_PROFILE_SCOPE("EndScene");
		SpriteRenderer::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	HZ_PROFILE_FUNCTION();

	p_pos = m_TextTrans->GetPosition();
	p_size = m_TextTrans->GetScale();

	ImGui::Begin("Debugger");

	ImGui::Checkbox("Render Background?", &isRenderBackground);
	ImGui::Text("DrawCalls: %lld", SpriteRenderer::GetState().DrawCalls);
	ImGui::Text("Frame: %f", 1.0f / Time::deltaTime());
	ImGui::Text("Current Plats Numbers: %d", curPlatNum);
	ImGui::Text("------------------");
	ImGui::ColorEdit3("Backgrond Color", glm::value_ptr(m_BackColor));
	ImGui::DragFloat("Jump velocity", &jump_vy, 0.1f, 10.0f, 60.0f, "%.2f", 1.0f);
	ImGui::DragFloat("Move velocity", &moveSpeed, 0.1f, 30.0f, 50.0f, "%.2f", 1.0f);
	ImGui::DragFloat3("Text Position", glm::value_ptr(p_pos), 0.2f, -512.0f, 512.0f, "%.2f", 1.0f);
	ImGui::DragFloat3("Text Scale", glm::value_ptr(p_size), 0.02f, -3.0f, 3.0f, "%.2f", 1.0f);

	ImGui::End();

	m_TextTrans->SetPosition(p_pos);
	m_TextTrans->SetScale(p_size);
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

void Sandbox2D::PlayerController()
{
	p_pos = player->m_Trans.GetPosition();
	p_size = player->m_Trans.GetScale();

	// --input------
	bool left = Input::IsKeyPressed(Key::A), right = Input::IsKeyPressed(Key::D);

	// --vx---------
	vx += Time::deltaTime() * (-(int)left + (int)right) * moveSpeed;

	if (left == right)
		abs(vx) > 0.01f ? vx *= dragRatio : vx = 0.0f;

	vx = glm::clamp(vx, -maxVX, maxVX);

	// --vy---------

	vy = isJump ? jump_vy : vy - gravity;

	// --pos x------
	p_pos.x += vx;
	if (p_pos.x < -maxWidth)p_pos.x += 2.0f * maxWidth;
	else if (p_pos.x > maxWidth)p_pos.x -= 2.0f * maxWidth;

	// --pos y------
	if (vy < 0 && !isGameOver)
	{
		float minDis = -vy;
		int minIndex = -1;
		float platY, playerY = player->GetChecker().y;
		isJump = false;
		for (size_t i = 0; i < plats.size(); i++)
		{
			if (!plats[i].IsDestroyed()) {
				plats[i].m_Color = { 0.8,0.8f,0.8,1.0 };
				if (plats[i].IsCollidedX(player->GetChecker().x))
				{
					plats[i].m_Color = { 1.0f,1.0f,1.0f,1.0 };
					platY = plats[i].GetPlatHeight();
					if (0 < playerY - platY)
					{
						if (playerY - platY < minDis) {
							plats[i].m_Color = { 1.0f,0.5f,0.5f,1.0 };
							isJump = true;
							minDis = playerY - platY;
							minIndex = (int)i;
						}
					}
				}
			}
		}

		if (vy < deadLine - playerY && deadLine - playerY < minDis)
		{
			//  game over
			combo = 0;
			isJump = false;
			isGameOver = true;
			//isJump = true;
			Log::Info("---------GAME OVER---------");
			//  do something
			p_pos.y += vy;
		}
		else if (isJump && !plats[minIndex].IsDestroyed())
		{
			auto& curPlat = plats[minIndex];
			auto platType = curPlat.m_Type;
			p_pos.y -= minDis;
			switch (platType)
			{
			case Plat::Type::NORMAL: {
				//p_pos.y -= minDis;
				break;
			}
			case Plat::Type::WEAK: {
				//p_pos.y -= minDis;
				curPlat.SetDestroyed(true);
				particle->Trigger(10,
					{ curPlat.m_Trans.GetPosition().x,
					curPlat.m_Trans.GetPosition().y, 0.5f },
					{ 10.0f,10.0f,1.0f },
					{ 0.8f,0.52f,0.0f,1.0f },
					25.0f,
					glm::clamp(-vy * 0.6f, 6.0f, 18.0f));
				break;
			}
			case Plat::Type::HORIZONTAL:
				break;
			default:
				break;
			}
			if (curID >= plats[minIndex].m_ID)
			{
				combo = 0;
			}
			else
			{
				maxCombo = std::max(maxCombo, ++combo);
			}

			particle->Trigger(
				glm::clamp(int(-vy * 0.3f), 2, 10),
				{ player->GetChecker().x, player->GetChecker().y + minDis, 0.5f },
				{ 10.0f,10.0f,1.0f },
				{ 0.52f,0.65f,0.16f,1.0f },
				15.0f,
				glm::clamp(-vy * 0.4f, 6.0f, 10.0f)
			);

			curID = plats[minIndex].m_ID;
			vy = -minDis;
		}
		else
		{
			isJump = false;
			p_pos.y += vy;
		}
	}
	else
	{
		isJump = false;
		p_pos.y += vy;
		if (p_pos.y > maxHeight)
			p_pos.y = maxHeight;
		else if (p_pos.y < quitLine) {
			//  quit
			isQuit = true;
			//  TODO: some thing
		}
	}
#pragma region Size conrtrol
	// --size x (as simple animation)
	if (left != right)
		p_size.x = left ? -std::abs(p_size.x) : std::abs(p_size.x);
#pragma endregion


#pragma region Apply
	// --apply------
	player->m_Trans.SetPosition(p_pos);
	player->m_Trans.SetScale(p_size);
#pragma endregion

}

void Sandbox2D::BackgroundContorller()
{
	HZ_PROFILE_FUNCTION();
	static int tmpScore;
	int bkrd = rand() % 10;
	if (player->m_Trans.GetPosition().y >= maxHeight && !isGameOver)
	{
		tmpScore += std::max(1, (int)(vy * 0.1f));
		m_BackColor.r = 0.8f + 0.15f * cos(0.02f * (float)tmpScore);
		for (size_t i = 0; i < back.size(); i++)
		{
			p_pos = back[i]->m_Trans.GetPosition();
			p_pos.y -= vy * 0.4f;
			if (p_pos.y < -600.0f) {
				if (bkrd < 5) {
					back[i]->m_Sprite = sp_back[rand() % (sp_back.size() - 1)];
				}
				else {
					back[i]->m_Sprite = sp_back[sp_back.size() - 1];
				}
				p_pos.y += 1200.0f;
			}
			back[i]->m_Trans.SetPosition(p_pos);
		}
	}
	else if (isGameOver) {
		tmpScore -= std::max(1, (int)(vy * 0.1f));
		m_BackColor.r = 0.8f + 0.15f * cos(0.01f * (float)tmpScore);
		for (size_t i = 0; i < back.size(); i++)
		{
			p_pos = back[i]->m_Trans.GetPosition();
			p_pos.y -= vy * 0.02f;
			if (p_pos.y > 600.0f) {
				if (bkrd < 3) {
					back[i]->m_Sprite = sp_back[rand() % (sp_back.size() - 1)];
				}
				else {
					back[i]->m_Sprite = sp_back[sp_back.size() - 1];
				}
				p_pos.y -= 1200.0f;
			}
			back[i]->m_Trans.SetPosition(p_pos);
		}
	}
}

void Sandbox2D::PlatsController()
{
	if (player->m_Trans.GetPosition().y >= maxHeight && !isGameOver)
	{
		curScore += static_cast<int>(vy * 10) / 100;
		std::sort(plats.begin(), plats.end(), [](Plat& a, Plat& b)
			{
				return a.GetPlatHeight() > b.GetPlatHeight();
			});
		auto curMaxHeight = plats[0].m_Trans.GetPosition().y;
		for (size_t i = 0; i < plats.size(); i++)
		{
			p_pos = plats[i].m_Trans.GetPosition();
			p_pos.y -= vy;
			if (p_pos.y < -520.0f)
			{
				p_pos.x = -270.0f + (float)(rand() % 540);
				p_pos.y = curMaxHeight + 1024.0f / curPlatNum - vy;
				curMaxHeight = p_pos.y;

				CreatePlat(plats[i]);
			}
			plats[i].m_Trans.SetPosition(p_pos);
			plats[i].Update();
		}
	}
	else if (isGameOver) {
		for (size_t i = 0; i < plats.size(); i++)
		{
			p_pos = plats[i].m_Trans.GetPosition();
			p_pos.y -= vy;
			plats[i].m_Trans.SetPosition(p_pos);
			plats[i].Update();
		}
	}
	else
	{
		for (auto& plat : plats)
		{
			plat.Update();
		}
	}
}

void Sandbox2D::DifficultyController()
{
	if (curScore < 100) {
		curPlatNum = maxPlatNum;
		normalPlatRatio = 100;
	}
	else if (curScore < 200) {
		curPlatNum = std::max(minPlatNum, maxPlatNum - 2);
		normalPlatRatio = 90;
	}
	else if (curScore < 300) {
		curPlatNum = std::max(minPlatNum, maxPlatNum - 4);
		normalPlatRatio = 80;
	}
	else if (curScore < 500) {
		curPlatNum = std::max(minPlatNum, maxPlatNum - 6);
		normalPlatRatio = 70;
	}
	else if (curScore < 800) {
		curPlatNum = std::max(minPlatNum, maxPlatNum - 8);
		normalPlatRatio = 60;
	}
	else if (curScore < 1100) {
		curPlatNum = std::max(minPlatNum, maxPlatNum - 10);
		normalPlatRatio = 55;
	}
	else if (curScore < 1400) {
		curPlatNum = std::max(minPlatNum, maxPlatNum - 12);
		normalPlatRatio = 50;
	}
	else if (curScore < 1700) {
		curPlatNum = std::max(minPlatNum, maxPlatNum - 13);
		normalPlatRatio = 45;
	}
	else if (curScore < 2000) {
		curPlatNum = std::max(minPlatNum, maxPlatNum - 14);
		normalPlatRatio = 40;
	}
}

void Sandbox2D::TextController()
{
	HZ_PROFILE_FUNCTION();
	if (isGameOver) {
		m_Text->SetText("Game Over\n\n> Score:\n> " + std::to_string(curScore)
			+ "/" + std::to_string(curRecord) + "\n\n"
			+ "> Combo:\n> " + std::to_string(maxCombo)
		);
		static glm::vec3 tmp_pos, tmp_size;
		p_pos = m_TextTrans->GetPosition();
		p_size = m_TextTrans->GetScale();

		p_pos = Math::SmoothDamp(p_pos, { -248.6f, 300.8f, 2.0f }, tmp_pos, 0.4f, glm::vec3(100.0f), Time::deltaTime() * 10.0f);
		p_size = Math::SmoothDamp(p_size, { 0.72f,0.72f,1.0f }, tmp_size, 0.4f, glm::vec3(100.0f), Time::deltaTime() * 10.0f);

		m_TextTrans->SetPosition(p_pos);
		m_TextTrans->SetScale(p_size);
	}
	else {
		m_Text->SetText("Score: " + std::to_string(curScore)
			+ "/" + std::to_string(curRecord) + "\n"
			+ "Combo: " + std::to_string(combo)
			+ "/" + std::to_string(maxCombo)
		);

	}
}

void Sandbox2D::CreatePlat(Plat& plat)
{
	int rd = rand() % 100;
	plat.Reset();
	int otherRatio = (100 - normalPlatRatio) / 2;
	if (rd < normalPlatRatio) {
		plat.m_Type = Plat::Type::NORMAL;
		plat.m_Sprite = sp_normalPlats[rand() % sp_normalPlats.size()];
	}
	else if (rd < normalPlatRatio + otherRatio) {
		plat.m_Type = Plat::Type::WEAK;
		plat.m_Sprite = sp_weakPlats[0];
	}
	else {
		plat.m_Type = Plat::Type::HORIZONTAL;
		plat.m_Sprite = sp_normalPlats[rand() % sp_normalPlats.size()];
	}
	/*else {

	}*/

	plat.m_Color = { 0.8,0.8f,0.8,1.0 };
	plat.m_ID = curMaxID++;
}
