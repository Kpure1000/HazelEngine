#pragma once

#include <Hazel.h>

#include <exception>

using namespace hazel;

class GameObject
{
public:

	GameObject()
		:m_Sprite(nullptr), m_Trans(std::make_shared<Transform>()),
		m_Shader(nullptr), m_Tex(nullptr)
	{
	}

	void SetVisible(bool visible) { m_Visible = visible; }
	bool IsVisible() { return m_Visible; }

	Ref<Sprite> m_Sprite;
	Ref<Transform> m_Trans;

	Ref<Shader> m_Shader;
	Ref<Texture2D> m_Tex;
private:

	bool m_Visible = true;

};

class Player : public GameObject
{
public:
	glm::vec2 GetChecker()
	{
		//  return temporary variable warning on release
		return std::move(glm::vec2(m_Trans->GetPosition().x,
			m_Trans->GetPosition().y - m_Trans->GetScale().y * m_Sprite->GetSize().y * 0.5f));
	}
};

class Plat : public GameObject
{
public:
	enum class Type
	{
		NORMAL,
		WEAK,
		HORIZONTAL,
	};

	Plat()
		:m_Color(1.0f), m_ID(0), m_Type(Type::NORMAL)
	{}

	Plat(Type type)
		:m_Color(1.0f), m_ID(0), m_Type(type)
	{}

	void Update()
	{
		switch (m_Type)
		{
		case Plat::Type::NORMAL:
			break;
		case Plat::Type::WEAK: {
			if (m_IsDestroyed) {
				if (m_Color.a > 0.05f) {
					m_Color.a = std::max(0.0f, m_Color.a - Time::deltaTime() * 1.7f);
				}
			}
			break;
		}
		case Plat::Type::HORIZONTAL: {
			if (curAnimateTime < animateTime) {
				curAnimateTime += 0.02f;
				m_Trans->SetPosition({
					m_Trans->GetPosition().x + moveSpeed,
					m_Trans->GetPosition().y,
					m_Trans->GetPosition().z
					});
			}
			else {
				curAnimateTime = 0.0f;
				moveSpeed = -moveSpeed;
			}
			break;
		}
		default:
			break;
		}
	}

	inline float GetPlatHeight() {
		return m_Trans->GetPosition().y
			+ m_Trans->GetScale().y * m_Sprite->GetSize().y * 0.50f;
	}

	bool IsCollided(const glm::vec2& checker)
	{
		if (IsCollidedX(checker.x))
			return false;
		return IsCollidedY(checker.y);
	}

	inline bool IsCollidedX(float x) {
		return m_Trans->GetPosition().x
			- m_Trans->GetScale().x * m_Sprite->GetSize().x * 0.75f < x
			&&
			m_Trans->GetPosition().x
			+ m_Trans->GetScale().x * m_Sprite->GetSize().x * 0.75f > x;
	}

	inline bool IsCollidedY(float y) {
		return m_Trans->GetPosition().y
			- m_Trans->GetScale().y * m_Sprite->GetSize().x * 0.0f < y // buttom
			&&
			m_Trans->GetPosition().y
			+ m_Trans->GetScale().y * m_Sprite->GetSize().x * 0.50f > y; // top
	}
	glm::vec4 m_Color;
	size_t m_ID;

	Type m_Type;

	bool m_IsJumped = false;

	void SetDestroyed(bool destroyed) { m_IsDestroyed = destroyed; }
	bool IsDestroyed() { return m_IsDestroyed; }

	void Reset()
	{
		m_IsJumped = false;
		m_IsDestroyed = false;
		moveSpeed = rand() % 2 == 0 ? 1.0f : -1.0f;
		curAnimateTime = 0;
	}

	float moveSpeed = 1.0f;
	float curAnimateTime = 0;
	float animateTime = 2.8f;

private:
	bool m_IsDestroyed = false;
};

template<typename _MeshT, size_t _Size>
class ParticleSystem
{
public:
	ParticleSystem(float MaxLifeTime = 0.0f)
		:maxLifeTime(MaxLifeTime)
	{}

	void Trigger(int number, const glm::vec3& position, const glm::vec4& color , float radius, float velocity)
	{
		glm::vec3 tmpVec;
		auto divRad = 1.0f / 180.0f;
		for (auto& it : m_Ptc)
		{
			if (number == 0)break;
			if (it.lifeTime < 0.0f) {
				tmpVec.x = position.x + radius * 0.01f * (float)(50 - rand() % 100);
				tmpVec.y = position.y + radius * 0.01f * (float)(50 - rand() % 100);
				tmpVec.z = position.z;
				it.m_Trans.SetPosition(tmpVec);
				tmpVec = velocity * glm::normalize(tmpVec - position);
				tmpVec.z = 0.0f;
				it.m_Vel = tmpVec;
				it.lifeTime = maxLifeTime;
				it.m_Color = color;
				it.m_Color.a = 1.0f;
				number--;
			}
		}
	}

	void Update(const float& gravity, const float& yOffset, const float dragRatio = 0.95f)
	{
		glm::vec3 tmpVec;
		float divLifeTime = 1.0f / maxLifeTime;
		for (auto& it : m_Ptc)
		{
			if (it.lifeTime > 0.0f) {
				it.m_Vel.y -= gravity;
				it.m_Vel *= dragRatio;
				tmpVec = it.m_Trans.GetPosition();
				tmpVec.x += it.m_Vel.x;
				tmpVec.y += (it.m_Vel.y + yOffset);
				it.m_Trans.SetPosition(tmpVec);
				it.m_Color.a = it.lifeTime * divLifeTime;
				it.lifeTime -= Time::deltaTime();
			}
		}
	}

	inline size_t size()const { return _Size; }

	struct Particle {
		_MeshT m_Mesh;
		Transform m_Trans;
		glm::vec4 m_Color;
		glm::vec3 m_Vel;
		float lifeTime = -1.0f;
	};

	inline std::array<Particle, _Size>& ptc() { return m_Ptc; }

	Ref<Shader> m_Shader;

	Ref<Texture2D> m_Tex;

	float maxLifeTime;

private:
	std::array<Particle, _Size> m_Ptc;

};
