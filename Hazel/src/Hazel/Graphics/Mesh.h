#pragma once

#include "Hazel/Core/Core.h"

#include "Vertex.h"
#include "Hazel/Graphics/Drawable.h"

#include <vector>

namespace hazel
{
	class Mesh : public Drawable
	{
    public:

        Mesh()
            :m_VAO(0), m_VBO(0), m_EBO(0)
        {}

        Mesh(std::vector<Vertex> Vertices, std::vector<unsigned int> Indices)
            :m_VAO(0), m_VBO(0), m_EBO(0), m_Vertices(Vertices), m_Indices(Indices)
        {}

        virtual ~Mesh() {}

    public:
        inline unsigned int GetVAO() { return m_VAO; }
        inline unsigned int GetVBO() { return m_VBO; }
        inline unsigned int GetEBO() { return m_EBO; }
        inline std::vector<Vertex> GetVertices() { return m_Vertices; }
        inline std::vector<unsigned int> GetIndices() { return m_Indices; }

    protected:

        virtual void Init() = 0;

        /**************************************************/

        unsigned int m_VAO, m_VBO, m_EBO;

        std::vector<Vertex> m_Vertices;

        std::vector<unsigned int> m_Indices;

	};
}

