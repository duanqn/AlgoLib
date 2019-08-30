#pragma once

namespace AlgoLib{
namespace Math{
    int gcd(int x, int y){
        return y == 0 ? x : gcd(y, x%y);
    }
}   // namespace Math
}   // namespace AlgoLib
