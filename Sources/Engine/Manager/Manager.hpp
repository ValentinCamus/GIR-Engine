#pragma once

#include <Core/Core.hpp>
#include <Engine/Component/Component.hpp>

namespace gir
{
    template<class T>
    class Manager
    {
    public:
        static const T* Get(const std::string& name);

        template<class... Ts>
        static void Add(Ts... args);

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
    const T* Manager<T>::Get(const std::string& name)
    {
        auto predicate = [&name](const std::unique_ptr<T>& elementUptr) { return elementUptr->GetName() == name; };

        auto it = std::find_if(m_elements.cbegin(), m_elements.cend(), predicate);

        GIR_ASSERT(it != m_elements.cend(), "Element \"" + name + "\" does not exist");

        return it->get();
    }

    template<class T>
    template<class... Ts>
    void Manager<T>::Add(Ts... args)
    {
        m_elements.emplace_back(std::move(std::make_unique<T>(args...)));
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