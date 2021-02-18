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
	/// <summary>
	/// Player controller
	/// </summary>
	void PlayerController();

	/// <summary>
	/// Background controller
	/// </summary>
	void BackgroundContorller();

	/// <summary>
	/// Jump plats controller
	/// </summary>
	void PlatsController();

private:
	hazel::Ref<hazel::ShaderManager> m_ShaderManager;
	hazel::OrthographicCameraController m_CameraController;

	hazel::Ref<hazel::Text> m_Text;
	hazel::Ref<hazel::Shader> m_TextShader;
	hazel::Ref<hazel::Transform> m_TextTrans;

	/// <summary>
	/// Player
	/// </summary>
	hazel::Ref<Player> player;

	/// <summary>
	/// Background
	/// </summary>
	std::array<Ref<GameObject>, 3> back;

	/// <summary>
	/// Jump plats
	/// </summary>
	std::vector<Ref<Plat>> plats;

	glm::vec3 p_pos;
	glm::vec3 p_size;

	float vy = 0.0f;
	const float gravity = 0.98f;
	float jump_vy = 19.0f;
	bool isJump = false;

	float vx = 0.0f;
	float moveSpeed = 35.0f;
	const float maxVX = 30.0f;
	const float dragRatio = 0.85f;

	const float maxWidth = 284.0f;
	const float maxHeight = 100.0f;
	const float deadLine = -525.0f;

	const int maxPlatNum = 28;
	int curPlatNum = maxPlatNum;


private:
	glm::vec3 m_QuadColor = { 0.68f,0.68f,0.68f };
};

