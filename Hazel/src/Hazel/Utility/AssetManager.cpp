#include "hzpch.h"

#include "AssetManager.h"

namespace hazel
{
	template<class T>
	const Ref<T> AssetManager<T>::Get(const std::string& name) const
	{
		if (IsExist(name))
		{
			return m_AssetLib.at(name);
		}
		return nullptr;
	}

	template<class T>
	const Ref<T> AssetManager<T>::Load()
	{
		Ref<T>asset;
		asset.reset((T::Create()));
		Add(asset);
		return asset;
	}

	template<class T>
	const Ref<T> AssetManager<T>::Load(const std::string& filePath)
	{
		Ref<T>asset;
		asset.reset((T::Create(filePath)));
		Add(asset);
		return asset;
	}

	template<class T>
	const Ref<T> AssetManager<T>::Load(const std::string& filePath, const std::string& name)
	{
		Ref<T>asset;
		asset.reset((T::Create(filePath)));
		Add(asset, name);
		return asset;
	}

	template<class T>
	void AssetManager<T>::Add(const std::string& name, const Ref<T>& asset)
	{
		if (IsExist(name))
		{
			Log::WarnCore("Asset '{0}' existed.", name);
			return;
		}
		asset->SetName(name);
		m_AssetLib[name] = asset;
	}

	template<class T>
	void AssetManager<T>::Add(const Ref<T>& asset)
	{
		Add(asset->GetName(), asset);
	}

	template<class T>
	bool AssetManager<T>::IsExist(const std::string& name) const
	{
		return m_AssetLib.find(name) != m_AssetLib.end();
	}
}