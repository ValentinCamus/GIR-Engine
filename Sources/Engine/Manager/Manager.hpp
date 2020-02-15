#pragma once

#include <Core/Core.hpp>
#include <Engine/Component/Component.hpp>

namespace gir
{
    template<class T>
    class Manager
    {
    public:
        static T* Get(const std::string& name);

        template<class... Ts>
        static T* Add(Ts&&... args);

        static void Remove(const std::string& name);

        static void Remove(const T* element);

        static bool Contains(const std::string& name);

        static bool Contains(const T* element);

        static void Clear();

    private:
        static std::vector<std::unique_ptr<T>> m_elements;
    };

    template<class T>
    std::vector<std::unique_ptr<T>> Manager<T>::m_elements {};

    template<class T>
    T* Manager<T>::Get(const std::string& name)
    {
        auto predicate = [&name](const std::unique_ptr<T>& elementUptr) { return elementUptr->GetName() == name; };

        auto it = std::find_if(m_elements.cbegin(), m_elements.cend(), predicate);

        if (it != m_elements.cend())
            return it->get();
        else
            return nullptr;
    }

    template<class T>
    template<class... Ts>
    T* Manager<T>::Add(Ts&&... args)
    {
        m_elements.emplace_back(std::move(std::make_unique<T>(std::forward<Ts>(args)...)));
        return m_elements.back().get();
    }

    template<class T>
    void Manager<T>::Remove(const std::string& name)
    {
        auto predicate = [&name](const std::unique_ptr<T>& elementUptr) { return elementUptr->GetName() == name; };

        m_elements.erase(std::remove_if(m_elements.begin(), m_elements.end(), predicate), m_elements.end());
    }

    template<class T>
    void Manager<T>::Remove(const T* element)
    {
        auto predicate = [element](const std::unique_ptr<T>& elementUptr) { return elementUptr.get() == element; };

        m_elements.erase(std::remove_if(m_elements.begin(), m_elements.end(), predicate), m_elements.end());
    }

    template<class T>
    bool Manager<T>::Contains(const std::string& name)
    {
        auto predicate = [&name](const std::unique_ptr<T>& elementUptr) { return elementUptr->GetName() == name; };

        return std::find_if(m_elements.cbegin(), m_elements.cend(), predicate) != m_elements.cend();
    }

    template<class T>
    bool Manager<T>::Contains(const T* element)
    {
        auto predicate = [element](const std::unique_ptr<T>& elementUptr) { return elementUptr.get() == element; };

        return std::find_if(m_elements.cbegin(), m_elements.cend(), predicate) != m_elements.cend();
    }

    template<class T>
    void Manager<T>::Clear()
    {
        m_elements.clear();
    }
} // namespace gir