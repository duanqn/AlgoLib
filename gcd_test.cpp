#include "gcd.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>

int main(){
    std::srand(std::time(nullptr));
    const int tests = 50;
    const int maxval = 9998;
    for(int t = 0; t < tests; ++t){
        int a = std::rand() % maxval + 2;
        int b = std::rand() % maxval + 2;
        int res = AlgoLib::Math::gcd(a, b);
        if(a % res != 0 || b % res != 0 || AlgoLib::Math::gcd(a / res, b / res) != 1){
            printf("AlgoLib::Math::gcd is faulty!\n");
            printf("===Data dump===\n");
            printf("Reported GCD for (%d, %d) is %d\n", a, b, res);
            return 1;
        }
    }

    printf("Running test for AlgoLib::Math::gcd ............ PASS\n");
    return 0;
}