#include "asyncExecution.hpp"
#include <cstdio>

void f(int x){
    printf("%d\n", x);
}

int main(){
    for(int i = 0; i < 50; ++i){
        AlgoLib::SyntaxSugar::AsyncExecution(false, f, i);
    }

    return 0;
}