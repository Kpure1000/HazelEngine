#pragma once
#include <memory>

#include "Hazel/Core/Core.h"

#include "Hazel/Log.h"

namespace hazel
{
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Bool, Mat3, Mat4
	};

	/// <summary>
	/// Get size of shader data type
	/// </summary>
	/// <param name="type">Shader data type</param>
	/// <returns>Size</returns>
	static size_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return sizeof(float);
		case ShaderDataType::Float2:   return sizeof(float) * 2;
		case ShaderDataType::Float3:   return sizeof(float) * 3;
		case ShaderDataType::Float4:   return sizeof(float) * 4;
		case ShaderDataType::Int:      return sizeof(int);
		case ShaderDataType::Int2:     return sizeof(int) * 2;
		case ShaderDataType::Int3:     return sizeof(int) * 3;
		case ShaderDataType::Int4:     return sizeof(int) * 4;
		case ShaderDataType::Bool:     return sizeof(bool);
		case ShaderDataType::Mat3:     return sizeof(float) * 3 * 3;
		case ShaderDataType::Mat4:     return sizeof(float) * 4 * 4;
		}
		Log::AssertCore(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		BufferElement() = default;
		BufferElement(ShaderDataType type, const std::string& name, bool isNormalized = false)
			:name(name), size(ShaderDataTypeSize(type)),
			type(type), offset(0), normalized(isNormalized)
		{
		}

		unsigned int GetElementCount()const;

		std::string name;
		ShaderDataType type;
		size_t size;
		size_t offset;
		bool normalized;
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}

		BufferLayout(std::initializer_list<BufferElement> ele)
			:m_Elements(ele), m_Stride(0)
		{
			CalOffsetAndStride();
		}

		inline unsigned int GetStride()const { return m_Stride; }

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalOffsetAndStride()
		{
			size_t offset = 0;
			for (auto& item : m_Elements)
			{
				item.offset = offset;
				offset += item.size;
				m_Stride += static_cast<unsigned int>(item.size);
			}
		}

		std::vector<BufferElement> m_Elements;
		unsigned int m_Stride = 0;
	};

	class HAZEL_API VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind()const = 0;
		virtual void UnBind()const = 0;

		virtual void SetData(const void* data, size_t size) = 0;

		virtual const BufferLayout& GetLayout()const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static  VertexBuffer* Create(float* vertices, size_t size);
	};

	class HAZEL_API IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind()const = 0;
		virtual void UnBind()const = 0;

		virtual size_t GetCount() = 0;

		static  IndexBuffer* Create(unsigned int* indices, size_t count);
	};
}