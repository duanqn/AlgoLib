#pragma once

#include "ITree.hpp"

namespace AlgoLib::DataStructure{
    template<typename NodeData, int Branch>
    class FixedBranchTreeNode : public ITreeNode<NodeData>{
        private:
        static_assert(Branch > 0);
        protected:
        FixedBranchTreeNode* m_childNodes[Branch];

        public:
        FixedBranchTreeNode(): ITreeNode<NodeData>(){
            for(int i = 0; i < Branch; ++i){
                m_childNodes[Branch] = nullptr;
            }
        }

        virtual ~FixedBranchTreeNode(){
            for(int i = 0; i < Branch; ++i){
                if(m_childNodes[i] != nullptr){
                    delete m_childNodes[i];
                }
            }
        }
    };
}