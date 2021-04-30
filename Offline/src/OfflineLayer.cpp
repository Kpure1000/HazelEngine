#include "OfflineLayer.h"

#include <ctime>

OfflineLayer::OfflineLayer()
	:m_CameraController((float)Application::GetInstance()->GetWindow().GetSize().x
		/ (float)Application::GetInstance()->GetWindow().GetSize().y, false, true)
{
	m_CameraController.EnableInput(true);
	m_CameraController.EnableZoom(true);

	m_Tex.reset(Texture2D::Create());
	m_Tex->LoadFromFile("../data/texture/plats.psd");

	m_Tex2.reset(Texture2D::Create());
	m_Tex2->LoadFromFile("../data/texture/sprite0.png");

}


void OfflineLayer::OnAttach()
{
	krt::KRTMath::Srand48((unsigned int)std::time(NULL));

	// init
	m_OutPutSize = { 1920,1080 };
	glm::vec3 ca_org = { 3.0f,1.5f,-3.0f };
	glm::vec3 ca_fl = { 0.0f,0.0f,-1.0f };
	auto camera = std::make_shared<krt::ProjectionCamera>(krt::ProjectionCamera(
		ca_org, ca_fl, 45.0f, (float)m_OutPutSize.x / (float)m_OutPutSize.y, 0.0f, (ca_org - ca_fl).length()
	));
	auto objects = std::make_shared<krt::List>();
	auto sp1 = std::make_shared<krt::SphereHit>();
	sp1->GetTransform().SetPosition({ 0.0f,0.0f,-1.0f });
	sp1->GetTransform().SetScale(glm::vec3(0.5f));
	auto sp2 = std::make_shared<krt::SphereHit>();
	sp2->GetTransform().SetPosition({ 1.0f,0.0f,-1.0f });
	sp2->GetTransform().SetScale(glm::vec3(0.5f));
	auto sp_gd = std::make_shared<krt::SphereHit>();
	sp_gd->GetTransform().SetPosition({ 0.0f,-100.5f, -1.0f });
	sp_gd->GetTransform().SetScale(glm::vec3(100.0f));
	objects->AddHitable(sp1);
	objects->AddHitable(sp2);
	objects->AddHitable(sp_gd);
	auto scene = std::make_shared<krt::Scene>(krt::Scene("Test", m_OutPutSize, camera, objects));

	m_ImageBuffer = std::make_shared<krt::ImageBuffer>(scene->GetSize().x, scene->GetSize().y);

	int samplerNumbers = 1000, depth = 4;

	m_Tracer = new krt::RayTracer(scene, samplerNumbers, depth);

	m_State = m_Tracer->GetState();

	m_Tracer->Start(*m_ImageBuffer, true);
	
	//m_Tex->LoadFromMemory(m_OutPutSize.x, m_OutPutSize.y, 3, m_ImageBuffer->GetData());

	m_Sprite = Sprite(m_Tex->GetSize());

	m_Trans.SetPosition({ 0.0f,0.0f,0.0f });
	m_Trans.SetScale({ 1.0f,1.0f,1.0f });
}

void OfflineLayer::OnDetch()
{
}

void OfflineLayer::OnUpdate()
{
	m_CameraController.OnUpdate();

	RenderCommand::Clear();
	RenderCommand::SetClearColor({ 0.3f,0.5f,0.7f,1.0f });

	SpriteRenderer::ResetState();

	SpriteRenderer::BeginScene(m_CameraController.GetCamera());

	//m_Tex->Bind(1);
	//m_Tex->UpdateFromMemory(m_OutPutSize.x, m_OutPutSize.y, 3, m_ImageBuffer->GetData());
	
	SpriteRenderer::Submit(m_Sprite, m_Trans, m_Tex);
	SpriteRenderer::Submit(m_Sprite, m_Trans, m_Tex2);


	SpriteRenderer::EndScene();

}

void OfflineLayer::OnImGuiRender()
{
	HZ_PROFILE_FUNCTION();

	m_State = m_Tracer->GetState();

	int total_progress = 0;
	for (auto progress : m_State.progress) {
		total_progress += progress.total;
	}

	//  Get current total progress
	int curProgress = 0;
	for (auto progress : m_State.progress) {
		curProgress += progress.current;
	}

	ImGui::Begin("Profile");
	//  TODO
	ImGui::Text("%lld DrawCalls", SpriteRenderer::GetState().DrawCalls);
	static float ddt = 400.0f;
	static float framePS = 0.0f;
	ddt += Time::deltaTime();
	if (ddt > 1.0f) {
		framePS = 1.0f / Time::deltaTime();
		ddt = 0.0f;
	}
	ImGui::Text("%f FPS", framePS);

	ImGui::Text("Progress: %d/%d, (%.3f%%)", curProgress,
		total_progress, (float)curProgress / (float)total_progress * 100.0f);

	if (curProgress >= total_progress) {
		ImGui::Text("‰÷»æÕÍ±œ.");
	}

	ImGui::End();
}

void OfflineLayer::OnEvent(Event& e)
{
	m_CameraController.OnEvent(e);
	auto evd = EventDispatcher(e);
	evd.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& ev)
		{
			if (ev.GetKeyCode() == Key::Escape)
			{
				Log::Info("Shutdown");
				m_Tracer->Shutdown();
				Application::GetInstance()->Close();
			}
			return false;
		});

	evd.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& ev)
		{
			Log::Info("Shutdown");
			m_Tracer->Shutdown();
			return false;
		});
}
