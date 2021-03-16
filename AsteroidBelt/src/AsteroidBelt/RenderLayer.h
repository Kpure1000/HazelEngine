#pragma once

#include <Hazel.h>

#include<imgui.h>

using namespace hazel;

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
	OrthographicCameraController m_CameraController;

	Sprite m_Sprite;
	Transform m_Trans;
	Ref<Texture2D> m_Tex;

};
