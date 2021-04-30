#pragma once

#include <Hazel.h>

#include <KRT.h>

#include<imgui.h>

using namespace hazel;

class OfflineLayer : public Layer
{
public:
	OfflineLayer();

	~OfflineLayer()
	{
		delete m_Tracer;
	}

	virtual void OnAttach() override;
	virtual void OnDetch() override;
	virtual void OnUpdate() override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Event& e) override;

private:
	OrthographicCameraController m_CameraController;

	Sprite m_Sprite;
	Transform m_Trans;
	Ref<Texture2D> m_Tex;
	Ref<Texture2D> m_Tex2;

	krt::RayTracer* m_Tracer;
	krt::TraceState m_State;
	glm::ivec2 m_OutPutSize;
	krt::Ref<krt::ImageBuffer> m_ImageBuffer;
	krt::ThreadPool* m_ThreadPool;

};
