#pragma once
#include <list>
#include <algorithm>
#include <iostream>

template<typename T>
class ObjectPool
{
private:
    std::list<T*> unused;
    std::list<T*> used;
    int maxSize;

public:
    ObjectPool(int initSize = 10)
    {
        for (int i = 0; i < initSize; i++)
        {
            auto obj = new T();
            unused.push_back(obj);
        }
    }

    ~ObjectPool()
    {
        for (auto obj : unused)
        {
            delete obj;
        }
        for (auto obj : used)
        {
            delete obj;
        }
    }

    T* Take()
    {
        if (unused.empty())
        {
            return nullptr;
        }

        auto obj = unused.front();
        unused.pop_front();
        used.push_back(obj);
        obj->SetActive(true);
        obj->Reset();
        std::cout << "Reused object from unused pool. Unused size: " << unused.size() << std::endl;
        return obj;
    }

    void Return(T* obj)
    {
        auto find = std::find(used.begin(), used.end(), obj);
        if (find != used.end())
        {
            used.erase(find); // used에서 제거
            obj->SetActive(false);
            unused.push_back(obj); // unused에 추가하여 재사용 가능하게 함
            std::cout << "Returned object to unused pool. Unused size: " << unused.size() << std::endl;
        }
        else
        {
            std::cerr << "Warning: Attempted to return an object not in the used list." << std::endl;
        }
    }

    const std::list<T*>& GetUsedList() const
    {
        return used;
    }
};
