#include "krtpch.h"

#include "../../include/Core/Buffer.h"

namespace krt {

	glm::vec3 FragBuffer::GetFrag(const glm::vec2& uv) const
	{
		int w = static_cast<int>(uv.x * static_cast<float>(width));
		int h = static_cast<int>(uv.y * static_cast<float>(height));
		return data[w + h * width];
	}

	glm::vec3 FragBuffer::GetFrag(const glm::ivec2& wh) const
	{
		return data[wh.x + wh.y * width];
	}

	void FragBuffer::WriteFrag(const glm::vec2& uv, const glm::vec3& color)
	{
		int w = static_cast<int>(uv.x * static_cast<float>(width));
		int h = static_cast<int>(uv.y * static_cast<float>(height));
		data[w + h * width] = color;
	}

	void FragBuffer::WriteFrag(const glm::ivec2& wh, const glm::vec3& color)
	{
		data[wh.x + wh.y * width] = color;
	}

	glm::vec3 ImageBuffer::GetPixel(const glm::vec2& uv) const
	{
		int w = static_cast<int>(uv.x * static_cast<float>(width));
		int h = static_cast<int>(uv.y * static_cast<float>(height));
		return {
			static_cast<float>(data[w * channel + h * width * channel]) / TO_RGB,
			static_cast<float>(data[w * channel + h * width * channel + 1] / TO_RGB),
			static_cast<float>(data[w * channel + h * width * channel + 2] / TO_RGB)
		};
	}

	glm::vec3 ImageBuffer::GetPixel(const glm::ivec2& wh) const
	{
		return {
			   static_cast<float>(data[wh.x * channel + wh.y * width * channel]) / TO_RGB,
			   static_cast<float>(data[wh.x * channel + wh.y * width * channel + 1] / TO_RGB),
			   static_cast<float>(data[wh.x * channel + wh.y * width * channel + 2] / TO_RGB)
		};
	}

	void ImageBuffer::WritePixel(const glm::vec2& uv, const glm::vec3& color)
	{
		int w = static_cast<int>(uv.x * static_cast<float>(width));
		int h = static_cast<int>(uv.y * static_cast<float>(height));
		data[w * channel + h * width * channel] = static_cast<unsigned char>(color.r * TO_RGB);
		data[w * channel + h * width * channel + 1] = static_cast<unsigned char>(color.g * TO_RGB);
		data[w * channel + h * width * channel + 2] = static_cast<unsigned char>(color.b * TO_RGB);
	}

	void ImageBuffer::WritePixel(const glm::ivec2& wh, const glm::vec3& color)
	{
		data[wh.x * channel + wh.y * width * channel] = static_cast<unsigned char>(color.r * TO_RGB);
		data[wh.x * channel + wh.y * width * channel + 1] = static_cast<unsigned char>(color.g * TO_RGB);
		data[wh.x * channel + wh.y * width * channel + 2] = static_cast<unsigned char>(color.b * TO_RGB);
	}

}