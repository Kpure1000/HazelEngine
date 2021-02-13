#pragma once

#include "Hazel/Core/Core.h"

namespace hazel
{

	template<class T>
	class HAZEL_API AssetManager
	{
	public:
		const Ref<T> Get(const std::string& name)const;

		[[maybe_unused]]
		const Ref<T> Load();

		const Ref<T> Load(const std::string& filePath);

		const Ref<T> Load(const std::string& filePath, const std::string& name);

		void Add(const std::string& name, const Ref<T>& asset);

		void Add(const Ref<T>& asset);


	private:
		bool IsExist(const std::string& name)const;

		std::unordered_map<std::string, Ref<T>> m_AssetLib;
	};

	

}