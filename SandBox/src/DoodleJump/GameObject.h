#pragma once

#include <Hazel.h>

using namespace hazel;

class GameObject
{
public:

	GameObject()
		:m_Mesh(nullptr), m_Trans(std::make_shared<Transform>()),
		m_Shader(nullptr), m_Tex(nullptr)
	{
	}

	Ref<Mesh> m_Mesh;
	Ref<Transform> m_Trans;

	Ref<Shader> m_Shader;
	Ref<Texture2D> m_Tex;

};

class Player : public GameObject
{
public:
	glm::vec2 GetChecker()
	{
		//  return temporary variable warning on release
		return std::move(glm::vec2(m_Trans->GetPosition().x, m_Trans->GetPosition().y - m_Trans->GetScale().y * 0.5f));
	}
};

class Plat : public GameObject
{
public:
	Plat()
		:_color(1.0f)
	{}

	inline float GetPlatHeight() { return m_Trans->GetPosition().y + m_Trans->GetScale().y * 0.50f; }

	bool IsCollided(const glm::vec2& checker)
	{
		if (IsCollidedX(checker.x))
			return false;
		return IsCollidedY(checker.y);
	}

	inline bool IsCollidedX(float x) {
		return m_Trans->GetPosition().x - m_Trans->GetScale().x * 0.75f < x
			&&
			m_Trans->GetPosition().x + m_Trans->GetScale().x * 0.75f > x;
	}

	inline bool IsCollidedY(float y) {
		return m_Trans->GetPosition().y - m_Trans->GetScale().y * 0.0f < y // buttom
			&&
			m_Trans->GetPosition().y + m_Trans->GetScale().y * 0.50f > y; // top
	}
	glm::vec4 _color;
};

template<typename T, int _Size>
class PlatQ
{
public:
	PlatQ()
		:_front(_Size - 1), _rear(0)
	{}

	inline T& Front() { return m_Plats[_front]; }
	inline T& Rear() { return m_Plats[_rear]; }

	void Forward()
	{
		_rear = (_rear + 1) % _Size;
		_front = (_front + 1) % _Size;
	}

	inline int GetSize() { return _Size; }

	inline T* GetPlats() { return m_Plats; }

private:
	T m_Plats[_Size];
	int _front, _rear;
};
