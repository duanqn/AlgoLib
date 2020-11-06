#include "matrix.hpp"
#include "squarematrix.hpp"
#include <utility>

int main(){
    size_t dim1 = 10;
    size_t dim2 = 10;

    AlgoLib::Math::Matrix<double> mat(std::make_pair(dim1, dim2));

    for(int i = 0; i < dim1; ++i){
        for(int j = 0; j < dim2; ++j){
            mat[i][j] = i;
        }
    }

    for(int i = 0; i < dim1; ++i){
        for(int j = 0; j < dim2; ++j){
            printf("%.3lf ", mat[i][j]);
        }
        printf("\n");
    }

    mat.T();

    for(int i = 0; i < dim1; ++i){
        for(int j = 0; j < dim2; ++j){
            printf("%.3lf ", mat[i][j]);
        }
        printf("\n");
    }

    return 0;
}