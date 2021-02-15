#pragma once

#include <Hazel.h>

using namespace hazel;

class GameObject
{
public:
	Ref<Mesh> m_Mesh;
	Ref<Transform> m_Trans;

	Ref<Shader> m_Shader;
	Ref<Texture2D> m_Tex;

};

class Player : public GameObject
{
public:
	Player()
	{
		m_Trans = std::make_shared<Transform>();
	}

	glm::vec2 GetChecker()
	{
		return { m_Trans->GetPosition().x, m_Trans->GetPosition().y - m_Trans->GetScale().y * 0.5f };
	}
};

class Plat : public GameObject
{
public:
	bool IsCollided(glm::vec2 checker)
	{
		glm::vec2 left_button{ m_Trans->GetPosition().x - m_Trans->GetScale().x * 0.5f,
		m_Trans->GetPosition().y - m_Trans->GetScale().y * 0.5f };
		glm::vec2 right_top{ m_Trans->GetPosition().x + m_Trans->GetScale().x * 0.5f,
		m_Trans->GetPosition().y + m_Trans->GetScale().y * 0.5f };
	}
};