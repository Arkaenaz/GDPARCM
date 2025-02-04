#pragma once

template <typename T>
class Singleton
{
public:
    static T* getInstance()
    {
        if (P_SHARED_INSTANCE == nullptr)
        {
            P_SHARED_INSTANCE = new T();
        }
        return P_SHARED_INSTANCE;
    }
protected:
    static T* P_SHARED_INSTANCE;

    Singleton() {}
    ~Singleton() {}
    Singleton(Singleton const&) {};
    Singleton& operator=(Singleton const&) {}  
};

template <class _class_>
_class_* Singleton<_class_>::P_SHARED_INSTANCE = nullptr;

