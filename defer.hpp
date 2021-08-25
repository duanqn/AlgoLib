#pragma once

#include <concepts>
#include <functional>

namespace AlgoLib::SyntaxSugar{
    template<typename Function, typename... Args> requires std::regular_invocable<Function, Args...>
    class Defer{
        private:
        public:
        Defer(Function&& f, Args&&... args);
        virtual ~Defer(){
            f(args);
        }
    };
}
