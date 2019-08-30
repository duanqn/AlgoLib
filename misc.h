/*
    misc.h -- small util functions
*/
#pragma once

namespace AlgoLib{
    int maxint(int x, int y){
        return x > y ? x : y;
    }

    int maxint3(int x, int y, int z){
        return maxint(x, maxint(y, z));
    }

    int absint(int x){
        return x < 0 ? -x : x;
    }
}   // namespace AlgoLib
