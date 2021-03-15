#include "hzpch.h"

#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace hazel
{

	void OpenGLRendererAPI::Init()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRendererAPI::SetViewPort(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawBuffered(const Ref<VertexArray>& vertexArray)
	{
		for (auto& vb : vertexArray->GetVertexBuffers())
		{
			vb->Bind();
			glDrawArrays(GL_TRIANGLES, 0, (unsigned int)vb->GetSize());
		}
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, size_t indexCount)
	{
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();

		glDrawElements(GL_TRIANGLES, (GLsizei)count, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	/*void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, (GLsizei)vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}*/

}