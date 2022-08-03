#include <cstdio>
#include "arraynd.hpp"
#include <vector>

int main(){
    std::array<size_t, 2> size2 {2147483647, 2147483647};

    AlgoLib::DataStructure::ArrayND<double, 2> *pArray2D;

    try{
        pArray2D = new AlgoLib::DataStructure::ArrayND<double, 2>(size2);
        delete pArray2D;
        printf("Failed to catch size overflow!\n");
        return 1;
    }
    catch(AlgoLib::Exception &e){
        printf("Exception code %d\n", e.code());
    }

    std::array<size_t, 3> size3 {21, 144, 4};

    AlgoLib::DataStructure::ArrayND<double, 3> *pArray3D;
    try{
        pArray3D = new AlgoLib::DataStructure::ArrayND<double, 3>(size3);
        AlgoLib::DataStructure::ArrayND<double, 3> &array = *pArray3D;
        auto t = array[0];
        t[4][2] = 441;
        array[2][100][0] = 50.37;
        printf("<2, 100, 0> = %lf\n", array[2][100][0]);
        printf("<0, 4, 2> = %lf\n", array[0][4][2]);
        delete pArray3D;
    }
    catch(AlgoLib::Exception &e){
        printf("Exception code %d\n", e.code());
        return 1;
    }
    
    return 0;
}