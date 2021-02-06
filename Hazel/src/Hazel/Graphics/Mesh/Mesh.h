#pragma once

#include "Hazel/Core/Core.h"

#include "../Vertex.h"
#include "Hazel/Graphics/Drawable.h"

#include "Hazel/Renderer/VertexArray.h"

#include <vector>

namespace hazel
{
    class Renderer;

	class Mesh : public Drawable
	{
    public:
        Mesh()
        {
            m_VertexArray.reset(VertexArray::Create());
        }

        const std::shared_ptr<VertexArray>& GetVertexArray()const
        {
            return m_VertexArray;
        }

    protected:

        friend class Renderer;

        std::shared_ptr<VertexArray> m_VertexArray;

	};
}

