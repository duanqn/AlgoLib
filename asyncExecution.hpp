#pragma once

#include <functional>
#include <thread>
#include <concepts>

namespace AlgoLib::SyntaxSugar{
    class AsyncExecution{
        private:
        std::thread m_worker;
        public:

        template<typename Function, typename... Args> requires std::regular_invocable<Function, Args...>&& std::is_same_v<std::invoke_result_t<Function, Args...>, void>
        AsyncExecution(Function&& f, Args&&... args);
        virtual ~AsyncExecution();
    };

    template<typename Function, typename... Args> requires std::regular_invocable<Function, Args...> && std::is_same_v<std::invoke_result_t<Function, Args...>, void>
    AsyncExecution::AsyncExecution(Function&& f, Args&&... args):
        m_worker(std::forward<Function>(f), std::forward<Args>(args)...) {}

    AsyncExecution::~AsyncExecution(){
        m_worker.join();
    }

}   // namespace AlgoLib::SyntaxSugar
