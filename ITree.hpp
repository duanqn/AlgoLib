#pragma once

namespace AlgoLib::DataStructure{
    template<typename NodeData>
    class ITreeNode{
        protected:
        NodeData m_data;

        ITreeNode(): m_data(){}
        ITreeNode(const NodeData &data): m_data(data){}
        ITreeNode(NodeData&& data): m_data(data){}

        public:
        virtual ~ITreeNode(){}
    };

    template<typename NodeData>
    class ITree{
        protected:
        ITreeNode<NodeData>* m_root;
        
        public:
        ITree(): m_root(nullptr){}
        virtual ~ITree(){
            if(m_root != nullptr){
                delete m_root;
            }
        }
    };
}   // AlgoLib::DataStructure
