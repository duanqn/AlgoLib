#pragma once

#include <functional>

namespace AlgoLib::SyntaxSugar{
    class TCleanup{
        private:
        std::function<void ()> m_func;

        // Do not dynamically allocate an object with this class
        static void * operator new(size_t) = delete;
        static void * operator new[](size_t) = delete;
        static void operator delete(void *) = delete;
        static void operator delete[](void *) = delete;

        public:
        TCleanup(std::function<void ()> const& func): m_func(func){}
        TCleanup(std::function<void ()> && func): m_func(func){}


        ~TCleanup(){
            m_func();
        }
    };
}   // namespace AlgoLib::SyntaxSugar
