/*
    misctemp.hpp -- small util functions using templates
*/
#pragma once

namespace AlgoLib{
    template <typename T>
    void swap(T& x, T& y){
        T t = x;
        x = y;
        y = t;
    }
}   // namespace AlgoLib
