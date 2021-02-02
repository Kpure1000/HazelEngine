#pragma once

#include "Hazel/Core/Core.h"
#include "Transform.h"

namespace hazel
{
	class HAZEL_API Drawable
	{
	public:

		Drawable() : m_isActived(true) {}

		inline Transform& GetTransform()
		{
			return m_trans;
		}

		inline Transform GetTransform()const
		{
			return m_trans;
		}

		inline void SetActive(bool active) { m_isActived = active; }

		inline bool isActive()const { return m_isActived; }

	protected:

		bool m_isActived;

		Transform m_trans;

	};
}
