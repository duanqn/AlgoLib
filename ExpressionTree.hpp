#pragma once

#include "scaleArray.hpp"

namespace AlgoLib::DataStructure{

    template<typename Operator, typename Value>
    class ExpressionTreeNode{
        private:
        Operator m_op;
        ScaleArray<Value> m_data;
        ScaleArray<ExpressionTreeNode *> m_childNodes;
        
        public:
    };

}   // AlgoLib::DataStructure
