#pragma once
template <typename T>
class ResourceMgr : public Singleton<ResourceMgr<T>>
{
	friend Singleton<ResourceMgr<T>>;
protected:
	std::unordered_map<std::string, T*> resources; 

	ResourceMgr() = default;
	~ResourceMgr() {
		UnloadAll();
	}
	ResourceMgr(const ResourceMgr&) = delete;
	ResourceMgr& operator=(const ResourceMgr&) = delete;

public:
	static T Empty;
	void UnloadAll()
	{
		for (const auto& pair : resources)
		{
			delete pair.second;
		}
		resources.clear();
	}

	bool Load(const std::string& id)
	{
		if (resources.find(id) != resources.end())
		{
			return false;
		}

		T* resource = new T();
		bool success = resource->loadFromFile(id); // loadFromFile()이 bool 값으로 반환함

		if (success)
		{
			// resources에 삽입
			resources.insert({ id, resource });
		}
		else
		{
			delete resource;
		}

		return true;
	}

	bool Unload(const std::string& id)
	{
		auto it = resources.find(id);

		if (it == resources.end())
		{
			return false;
		}
		delete it->second;
		resources.erase(it);
		return true;
	}

	T& Get(const std::string& id)
	{
		auto it = resources.find(id);
		if (it == resources.end())
		{
			return Empty;
		}
		return *(it->second);
	}
};

template<typename T>
T ResourceMgr<T>::Empty;

#define TEXTURE_MGR ResourceMgr<sf::Texture>::Instance()
#define FONT_MGR ResourceMgr<sf::Font>::Instance()
#define SOUNDBUFFER_MGR ResourceMgr<sf::SoundBuffer>::Instance()