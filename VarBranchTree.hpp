#pragma once

#include "ITree.hpp"
#include "scaleArray.hpp"

namespace AlgoLib::DataStructure{
    template<typename NodeData>
    class VarBranchTreeNode : public ITreeNode<NodeData>{
        private:
        protected:
        ScaleArray<Node*> m_childNodes;

        public:
        VarBranchTree(): ITreeNode<NodeData>(), m_childNodes(){}

        virtual ~VarBranchTree(){
            for(int i = 0; i < m_childNodes.size(); ++i){
                if(m_childNodes[i] != nullptr){
                    delete m_childNodes[i];
                }
            }
        }
    };
}   // AlgoLib::DataStructure