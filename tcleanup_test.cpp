#include "tcleanup.h"

void f(){
    int volatile *ptr = new int;
    *ptr = 5;

    AlgoLib::SyntaxSugar::TCleanup obj([&]{
        printf("[Second line] addr: %p value: %d\n", (void *)ptr, *ptr);
        delete ptr;
    });

    printf("[First line] Hello, world!\n");
    *ptr = (int)ptr;
}

int main(){
    f();
    return 0;
}