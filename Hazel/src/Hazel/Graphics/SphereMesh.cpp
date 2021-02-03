#include "hzpch.h"

#include <glad/glad.h>

#include "SphereMesh.h"

namespace hazel
{
	void SphereMesh::Init()
	{
		int latitu = m_lerpNum, longitu = m_lerpNum;

		float rz1, rz2, rxy1, rxy2;
		Vertex va, vb, vc, vd;
		glm::vec3 tmp_normal;
		for (size_t i = 0; i < longitu; i++)
		{
			for (size_t j = 0; j < latitu; j++)
			{
				rz1 = (glm::pi<float>() * j / latitu);
				rz2 = (glm::pi<float>() * (j + 1) / latitu);
				rxy1 = 2 * glm::pi<float>() * i / longitu;
				rxy2 = 2 * glm::pi<float>() * (i + 1) / longitu;
				va.position = { sin(rz1) * cos(rxy1), sin(rz1) * sin(rxy1), cos(rz1) };
				vb.position = { sin(rz2) * cos(rxy1), sin(rz2) * sin(rxy1), cos(rz2) };
				vc.position = { sin(rz2) * cos(rxy2), sin(rz2) * sin(rxy2), cos(rz2) };
				vd.position = { sin(rz1) * cos(rxy2), sin(rz1) * sin(rxy2), cos(rz1) };

				tmp_normal = glm::normalize(
					glm::cross(vd.position - vb.position, va.position - vc.position));
				va.normal = vb.normal = vc.normal = vd.normal = tmp_normal;

				va.texCoords.x = (float)i / longitu;
				va.texCoords.y = (float)j / longitu;

				vb.texCoords.x = (float)i / longitu;
				vb.texCoords.y = (float)(j + 1) / longitu;

				vc.texCoords.x = (float)(i + 1) / longitu;
				vc.texCoords.y = (float)(j + 1) / longitu;

				vd.texCoords.x = (float)(i + 1) / longitu;
				vd.texCoords.y = (float)j / longitu;

				m_Vertices.push_back(va);
				m_Vertices.push_back(vb);
				m_Vertices.push_back(vd);
				m_Vertices.push_back(vb);
				m_Vertices.push_back(vc);
				m_Vertices.push_back(vd);

			}
		}

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0], GL_STATIC_DRAW);

		//  position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(0);
		//  normal
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(1);
		//  texcoords
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
	}
}