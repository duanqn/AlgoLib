#include "strsplit.hpp"
#include <string>
#include <cstdio>
#include "scaleArray.hpp"

int main(){
    std::string str = "A, B, C;";
    std::u8string str2 = u8"测;试";
    auto list = AlgoLib::String::split<char, false>(str, ',');
    if(list[0] == "A" && list[1] == " B" && list[2] == " C;"){

    }
    else{
        printf("Test failed.\n");
        return 1;
    }

    auto list2 = AlgoLib::String::split(str2, u8';');
    if(list2[0] == u8"测" && list2[1] == u8"试"){

    }
    else{
        printf("Test failed.\n");
        return 1;
    }

    printf("strsplit test passed.\n");
    return 0;
}