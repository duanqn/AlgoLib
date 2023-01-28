#pragma once

#include <concepts>
#include <functional>

namespace AlgoLib::SyntaxSugar{
    template<typename Function, typename... Args> requires std::regular_invocable<Function, Args...>
    class Defer{
        private:
        std::function<void()> m_func;
        public:
            Defer(Function&& f, Args&&... args) : m_func([&]() {
                f(std::forward<Args>(args)...);
            }) {}
        virtual ~Defer(){
            m_func();
        }
    };
}
