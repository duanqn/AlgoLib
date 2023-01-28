#include "LockFreeQueue.hpp"
#include "asyncExecution.hpp"

#include <numeric>

using namespace AlgoLib::DataStructure;

using TargetType = AlgoLib::DataStructure::MTQueue<int, 1000, 10>;

void putInt(TargetType* queue, int id){
    for(int i = 0; i < 100; ++i){
        queue->enqueue(i, id);
    }
}

int main(){
    TargetType queue;

    {
        std::vector<std::unique_ptr<AlgoLib::SyntaxSugar::AsyncExecution>> executors(10);
        for (int i = 0; i < executors.size(); ++i) {
            executors[i] = std::make_unique<AlgoLib::SyntaxSugar::AsyncExecution>(putInt, &queue, i);
        }
    }

    int sum = 0;
    while(!queue.empty()){
        sum += queue.dequeue();
    }

    printf("Sum (should be 49500):%d\n", sum);

    return 0;
}
