#pragma once
#include "Core.h"
#include <glm/glm.hpp>

namespace krt {

	class KRT_API IBufferBase {
	public:
		IBufferBase(int width, int height) :width(width), height(height) {}

		int GetWidth() const { return width; }
		int GetHeight() const { return height; }

		virtual size_t GetSize() const = 0;

	protected:
		int width, height;
	};

	class KRT_API FragBuffer : public IBufferBase {
	public:
		FragBuffer(int width, int height)
			:IBufferBase(width, height)
		{
			data.resize((size_t)width * (size_t)height, glm::vec3(0.0f));
		}

		virtual size_t GetSize() const override { return data.size(); }

	public:
		inline operator const glm::vec3* () const { return data.data(); }

		inline const glm::vec3* GetData() const { return data.data(); }

		glm::vec3 GetFrag(const glm::vec2& uv) const;

		glm::vec3 GetFrag(const glm::ivec2& wh) const;

		void WriteFrag(const glm::vec2& uv, const glm::vec3& color);

		void WriteFrag(const glm::ivec2& wh, const glm::vec3& color);

	private:
		std::vector<glm::vec3> data;
	};

	class KRT_API ImageBuffer : public IBufferBase {
	public:
		ImageBuffer(int width, int height)
			:IBufferBase(width, height), channel(3)
		{
			size = (size_t)width * (size_t)height * (size_t)channel;
			data = new unsigned char [size];
		}

		virtual size_t GetSize() const override { return size; }

	public:
		int GetChannel() const { return channel; }

		inline operator const unsigned char* () const { return data; }

		inline const unsigned char* GetData() const { return data; }

		inline unsigned char* GetData() { return data; }

		glm::vec3 GetPixel(const glm::vec2& uv) const;

		glm::vec3 GetPixel(const glm::ivec2& wh) const;

		void WritePixel(const glm::vec2& uv, const glm::vec3& color);

		void WritePixel(const glm::ivec2& wh, const glm::vec3& color);

	private:
		int channel;
		int size;
		unsigned char* data;
	};

}