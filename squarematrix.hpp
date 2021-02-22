#pragma once

#include "matrix.hpp"

namespace AlgoLib::Math{
    template<typename DataType>
    class SquareMatrix: public Matrix<DataType>{
        private:
        public:
        SquareMatrix(size_t size): Matrix<DataType>(std::vector<size_t>(2, size){}
        virtual ~SquareMatrix();
    };
}