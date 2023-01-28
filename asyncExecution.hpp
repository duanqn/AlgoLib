#pragma once

#include <functional>
#include <thread>
#include <concepts>

namespace AlgoLib::SyntaxSugar{
    class AsyncExecution{
        private:
        std::thread m_worker;
        bool const m_wait;
        public:

        template<typename Function, typename... Args> requires std::regular_invocable<Function, Args...>&& std::is_same_v<std::invoke_result_t<Function, Args...>, void>
        AsyncExecution(bool waitUntilFinish, Function&& f, Args&&... args);
        virtual ~AsyncExecution();
    };

    template<typename Function, typename... Args> requires std::regular_invocable<Function, Args...> && std::is_same_v<std::invoke_result_t<Function, Args...>, void>
    AsyncExecution::AsyncExecution(bool waitUntilFinish, Function&& f, Args&&... args):
        m_worker(std::forward<Function>(f), std::forward<Args>(args)...),
        m_wait(waitUntilFinish){}

    AsyncExecution::~AsyncExecution(){
        if(m_wait){
            m_worker.join();
        }
        else{
            m_worker.detach();
        }
    }

}   // namespace AlgoLib::SyntaxSugar
