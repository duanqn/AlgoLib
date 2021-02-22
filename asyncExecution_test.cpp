#include "asyncExecution.hpp"
#include <cstdio>

void f(int x, int y){
    printf("%d\n", x*y);
}

int main(){
    for(int i = 0; i < 50; ++i){
        AlgoLib::SyntaxSugar::AsyncExecution(false, f, i, i+1);
    }

    return 0;
}