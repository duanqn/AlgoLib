#include "asyncExecution.hpp"
#include <cstdio>
#include <memory>

void f(int x){
    printf("%d\n", x);
}

int main(){
    std::vector<std::unique_ptr<AlgoLib::SyntaxSugar::AsyncExecution>> executors(50);
    for(int i = 0; i < executors.size(); ++i) {
        executors[i] = std::make_unique<AlgoLib::SyntaxSugar::AsyncExecution>(true, f, i);
    }

    return 0;
}