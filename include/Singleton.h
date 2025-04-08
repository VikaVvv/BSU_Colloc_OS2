#pragma once

#include <mutex>
#include <memory>
#include <atomic>

// Исправленные стратегии создания (теперь они шаблонные классы)
template <typename> 
struct CreateUsingNew {
    static typename std::remove_all_extents<T>::type* Create() {
        return new typename std::remove_all_extents<T>::type();
    }
    
    static void Destroy(typename std::remove_all_extents<T>::type* p) {
        delete p;
    }
};

template <typename> 
struct CreateStatic {
    static typename std::remove_all_extents<T>::type* Create() {
        static typename std::remove_all_extents<T>::type instance;
        return &instance;
    }
    
    static void Destroy(typename std::remove_all_extents<T>::type*) {
        // Ничего не делаем для статического объекта
    }
};

// Стратегии синхронизации
class NoLocking {
protected:
    class Lock {
    public:
        Lock() {}
        ~Lock() {}
    };
};

class ClassLevelLocking {
protected:
    class Lock {
    public:
        Lock() { mtx_.lock(); }
        ~Lock() { mtx_.unlock(); }
    private:
        static std::mutex mtx_;
    };
};

// Инициализация статического члена
std::mutex ClassLevelLocking::Lock::mtx_;

// Основной шаблон Singleton
template <typename T, 
          template <typename> class CreationPolicy = CreateUsingNew,
          class ThreadingModel = NoLocking>
class SingletonHolder : private ThreadingModel {
public:
    SingletonHolder(const SingletonHolder&) = delete;
    SingletonHolder& operator=(const SingletonHolder&) = delete;
    
    static T& Instance() {
        if (!pInstance_) {
            typename ThreadingModel::Lock guard;
            if (!pInstance_) {
                pInstance_ = CreationPolicy<T>::Create();
                atexit(&DestroySingleton);
            }
        }
        return *pInstance_;
    }
    
protected:
    SingletonHolder() = default;
    ~SingletonHolder() = default;
    
    static void DestroySingleton() {
        CreationPolicy<T>::Destroy(pInstance_);
        pInstance_ = nullptr;
    }
    
private:
    static T* pInstance_;
};

// Инициализация статического члена
template <typename T, template <typename> class CP, class TM>
T* SingletonHolder<T, CP, TM>::pInstance_ = nullptr;