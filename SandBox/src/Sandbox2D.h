#pragma once

#include <Hazel.h>
#include "DoodleJump/GameObject.h"

class Sandbox2D : public hazel::Layer
{
public:
	Sandbox2D();

	virtual void OnAttach() override;
	virtual void OnDetch() override;
	virtual void OnUpdate() override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(hazel::Event& ev) override;

private:
	void PlayerControl();
	void BackgroundContorl();

private:
	hazel::Ref<hazel::ShaderManager> m_ShaderManager;
	hazel::OrthographicCameraController m_CameraController;

	std::vector<Plat> plats;
	hazel::Ref<Player> player;

	std::array<Ref<Player>, 3> back;

	glm::vec3 p_pos;
	glm::vec3 p_size;
	float vy = 0.0f;

	const float maxHeight = 0.0f;
	const float gravity = 0.015f;
	float jump_vy = 0.5f;

private:
	glm::vec3 m_QuadColor = { 1.0f,1.0f,1.0f };
};

