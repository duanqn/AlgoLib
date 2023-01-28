#include "defer.hpp"

void f(){
    int *ptr = new int;
    *ptr = 5;

    AlgoLib::SyntaxSugar::Defer obj([&]{
        printf("[Second line] addr: %p value: %d\n", (void *)ptr, *ptr);
        delete ptr;
    });

    printf("[First line] Hello, world!\n");
}

int main(){
    f();
    return 0;
}