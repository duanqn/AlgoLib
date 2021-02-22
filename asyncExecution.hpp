#pragma once

#include <functional>
#include <thread>

namespace AlgoLib::SyntaxSugar{
    template<typename Function, typename... Args>
    class AsyncExecution{
        private:
        std::thread m_worker;
        bool const m_wait;
        public:
        AsyncExecution(bool waitUntioFinish, Function&& f, Args&&... args);
        virtual ~AsyncExecution();
    };

    template<typename Function, typename... Args>
    AsyncExecution<Function, Args...>::AsyncExecution(bool waitUntioFinish, Function&& f, Args&&... args):
        m_worker(std::forward<Function>(f), std::forward<Args>(args)...),
        m_wait(waitUntioFinish){}

    template<typename Function, typename... Args>
    AsyncExecution<Function, Args...>::~AsyncExecution(){
        if(m_wait){
            m_worker.join();
        }
        else{
            m_worker.detach();
        }
    }

}   // namespace AlgoLib::SyntaxSugar
