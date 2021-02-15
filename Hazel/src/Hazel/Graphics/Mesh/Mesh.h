#pragma once

#include "Hazel/Core/Core.h"

#include "Hazel/Renderer/VertexArray.h"

#include <vector>

namespace hazel
{
    class Renderer;

	class Mesh
	{
    public:
        Mesh()
        {
            m_VertexArray.reset(VertexArray::Create());
        }

        const Ref<VertexArray>& GetVertexArray()const
        {
            return m_VertexArray;
        }

    protected:

        friend class Renderer;

        Ref<VertexArray> m_VertexArray;

	};
}

